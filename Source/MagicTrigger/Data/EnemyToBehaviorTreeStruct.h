// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для передачи данных от врага к BehaviorTree.
 */

#pragma once

#include "EnemyToBehaviorTreeStruct.generated.h"

USTRUCT(BlueprintType)
struct FEnemyToBehaviorTreeStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyToBehaviorTreeStruct")
		float WaitTimeOfAnimationRoaring;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyToBehaviorTreeStruct")
		float FindPlayerRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyToBehaviorTreeStruct")
		float MoveAndAttackRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyToBehaviorTreeStruct")
		float AttackRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyToBehaviorTreeStruct")
		float PatrolingRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyToBehaviorTreeStruct")
		float PatrolingWaitTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyToBehaviorTreeStruct")
		FVector SpawnLocation;

};