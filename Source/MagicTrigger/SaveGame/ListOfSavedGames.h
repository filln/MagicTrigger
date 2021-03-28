// Fill out your copyright notice in the Description page of Project Settings.

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

	TArray<FString> ListOfSavedGames;
};
