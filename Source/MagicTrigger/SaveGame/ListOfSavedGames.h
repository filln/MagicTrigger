// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Список сохраненных игр.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ListOfSavedGames.generated.h"

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UListOfSavedGames : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
		TArray<FString> ListOfSavedGames;
};
