// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для взаимодействия с AnimationManager
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "AnimationManagerInterface.generated.h"

class UActorComponent;

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "AnimationManagerInterface")
class UAnimationManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API IAnimationManagerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * Setters
	 */
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
	//	void SetGettingDamage_IF(bool bGettingDamage);

};
