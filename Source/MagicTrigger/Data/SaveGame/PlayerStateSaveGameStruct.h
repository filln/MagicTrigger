// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Содержит характеристики перса, которые будут передаваться в сохраненные игры.
 */

#pragma once

#include "PlayerStateSaveGameStruct.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStateSaveGameStruct
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSaveGameStruct")
		float Life;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSaveGameStruct")
		float Defence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSaveGameStruct")
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSaveGameStruct")
		float MaxLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSaveGameStruct")
		float MaxDefence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSaveGameStruct")
		float MaxDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateSaveGameStruct")
		float MultiplierOfDamage;

	FPlayerStateSaveGameStruct()
	{
		Life = 100;
		Defence = 100;
		Damage = 100;
		MaxLife = 100;
		MaxDefence = 100;
		MaxDamage = 100;
		MultiplierOfDamage = 1;
	}

	FPlayerStateSaveGameStruct
	(
		float InLife,
		float InDefence,
		float InDamage,
		float InMaxLife,
		float InMaxDefence,
		float InMaxDamage,
		float InMultiplierOfDamage
	)
	{
		Life = InLife;
		Defence = InDefence;
		Damage = InDamage;
		MaxLife = InMaxLife;
		MaxDefence = InMaxDefence;
		MaxDamage = InMaxDamage;
		MultiplierOfDamage = InMultiplierOfDamage;
	}
};
