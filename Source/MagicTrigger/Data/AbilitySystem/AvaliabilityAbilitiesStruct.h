// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Состояние доступности абилок персу.
 */

#pragma once

#include "AvaliabilityAbilitiesStruct.generated.h"

USTRUCT(BlueprintType)
struct FAvaliabilityAbilitiesStruct
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AvaliabilityAbilitiesStruct")
		bool bMelee;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AvaliabilityAbilitiesStruct")
		bool bThrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AvaliabilityAbilitiesStruct")
		bool bSFSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AvaliabilityAbilitiesStruct")
		bool bRoundWave;

	/**
	 *true - абилка доступна
	 *false - абилка недоступна
	 */
	FAvaliabilityAbilitiesStruct()
	{
		bMelee = true;
		bThrow = true;
		bSFSphere = false;
		bRoundWave = true;
	}
};
