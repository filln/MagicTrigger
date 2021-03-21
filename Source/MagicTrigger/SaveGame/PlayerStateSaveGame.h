// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerStateSaveGame.generated.h"

class UTextureRenderTarget2D;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UPlayerStateSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UTextureRenderTarget2D* ScreenShot;

};
