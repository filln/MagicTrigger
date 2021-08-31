// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для сохранения данных перса.
 */

#pragma once

#include "PlayerCharacterSaveGameStruct.generated.h"

USTRUCT(BlueprintType)
struct FPlayerCharacterSaveGameStruct
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterSaveGameStruct")
		FVector Location;

	FPlayerCharacterSaveGameStruct()
	{
		Location = FVector(0);
	}
};
