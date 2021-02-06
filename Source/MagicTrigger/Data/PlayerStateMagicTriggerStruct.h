// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Содержит характеристики перса, которые будут передаваться в сохраненные игры.
 */

#pragma once

#include "PlayerStateMagicTriggerStruct.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStateMagicTriggerStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTriggerStruct")
		float Life;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTriggerStruct")
		float Defence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTriggerStruct")
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTriggerStruct")
		float MaxLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTriggerStruct")
		float MaxDefence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTriggerStruct")
		float MaxDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTriggerStruct")
		float MultiplierOfDamage;

	FPlayerStateMagicTriggerStruct()
	{
		Life = 100;
		Defence = 10;
		Damage = 80;
		MaxLife = 100;
		MaxDefence = 100;
		MaxDamage = 100;
		MultiplierOfDamage = 1;
	}
};
