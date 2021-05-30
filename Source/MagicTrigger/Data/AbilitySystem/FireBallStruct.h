// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для хранения и передачи данных абилки FireBall
 */

#pragma once


#include "FireBallStruct.generated.h"

USTRUCT(BlueprintType)
struct FFireBallStruct
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallStruct")
		float TimeInOwnersHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallStruct")
		float MaxMultiplierOfScaleInOwnersHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallStruct")
		float MaxEmissiveMultiplierInOwnersHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallStruct")
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallStruct")
		float MultiplierOfDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallStruct")
		float SpeedOfMoveToTarget;

	FFireBallStruct()
	{
		TimeInOwnersHand = 1.18;
		MaxMultiplierOfScaleInOwnersHand = 4.5;
		MaxEmissiveMultiplierInOwnersHand = 100;
		Damage = 400;
		MultiplierOfDamage = 1;
		SpeedOfMoveToTarget = 4200;
	}


};