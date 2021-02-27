// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для хранения имен ключей Blackboard
 */

#pragma once

#include "BlackboardKeyNamesStruct.generated.h"

USTRUCT(BlueprintType)
struct FBlackboardKeyNamesStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackboardKeyNamesStruct")
		FName TargetPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackboardKeyNamesStruct")
		FName bRoaring;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackboardKeyNamesStruct")
		FName bCanAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackboardKeyNamesStruct")
		FName bCanMoveToPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackboardKeyNamesStruct")
		FName bCanMoveAndAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackboardKeyNamesStruct")
		FName AcceptanceRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackboardKeyNamesStruct")
		FName bPlayerFound;
public:

	FBlackboardKeyNamesStruct()
	{
		TargetPlayer = FName(TEXT("TargetPlayer"));
		bRoaring = FName(TEXT("bRoaring"));
		bCanAttack = FName(TEXT("bCanAttack"));
		bCanMoveToPlayer = FName(TEXT("bCanMoveToPlayer"));
		bCanMoveAndAttack = FName(TEXT("bCanMoveAndAttack"));
		AcceptanceRadius = FName(TEXT("AcceptanceRadius"));
		bPlayerFound = FName(TEXT("bPlayerFound"));
	}

};