// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * ��� �������� ������ �� ����� � BehaviorTree.
 */

#pragma once

class UAnimationAsset;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyToBehaviorTreeStruct")
		UAnimationAsset* AnimationRoaring;

	FEnemyToBehaviorTreeStruct()
	{
		WaitTimeOfAnimationRoaring = 0;
		FindPlayerRadius = 0;
		MoveAndAttackRadius = 0;
		AttackRadius = 0;
		PatrolingRadius = 0;
		PatrolingWaitTime = 0;
		SpawnLocation = FVector(0);
		AnimationRoaring = nullptr;
	}


};