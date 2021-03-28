// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MagicTrigger\Interfaces\GameModeInterface.h"
#include "GameModeMagicTrigger.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API AGameModeMagicTrigger : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()
	
public:
	AGameModeMagicTrigger();



};
