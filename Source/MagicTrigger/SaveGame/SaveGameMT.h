// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Сохраненная игра.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MagicTrigger/Data/SaveGame/PlayerStateSaveGameStruct.h"
#include "MagicTrigger/Data/SaveGame/PlayerCharacterSaveGameStruct.h"
#include "MagicTrigger/Data/SaveGame/LevelSaveGameStruct.h"
#include "SaveGameMT.generated.h"


/**
 *
 */
UCLASS()
class MAGICTRIGGER_API USaveGameMT : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FLevelSaveGameStruct LevelSaveGameStruct;
	UPROPERTY()
		FPlayerCharacterSaveGameStruct PlayerCharacterSaveGameStruct;
	UPROPERTY()
		FPlayerStateSaveGameStruct StatesStruct;

};
