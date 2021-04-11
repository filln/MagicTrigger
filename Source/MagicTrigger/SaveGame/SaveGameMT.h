// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MagicTrigger\Data\PlayerStateMagicTriggerStruct.h"
#include "SaveGameMT.generated.h"

class UTextureRenderTarget2D;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API USaveGameMT : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
		UTextureRenderTarget2D* ScreenShot;
	UPROPERTY()
		FVector PlayerLocation;
	UPROPERTY()
		FName LevelName;
	UPROPERTY()
		FPlayerStateMagicTriggerStruct StatesStruct;

};
