﻿// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для сохранения данных уровня.
 */

#pragma once

#include "LevelSaveGameStruct.generated.h"

class UTextureRenderTarget2D;

USTRUCT(BlueprintType)
struct FLevelSaveGameStruct
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSaveGameStruct")
		FName LevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelSaveGameStruct")
		UTextureRenderTarget2D* ScreenShot;
};
