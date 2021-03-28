// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MagicTrigger\Data\PlayerStateMagicTriggerStruct.h"
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
	FVector PlayerLocation;
	FName LevelName;
	FPlayerStateMagicTriggerStruct StatesStruct;


public:
	/**
	 * 
	 */
	void SetStates(FVector InPlayerLocation, UTextureRenderTarget2D* InScreenShot, FName InLevelName, FPlayerStateMagicTriggerStruct InStatesStruct);
	/**
	 * 
	 */
	FPlayerStateMagicTriggerStruct GetStates() const;
	/**
	 * 
	 */
	FVector GetPlayerLocation() const;
};
