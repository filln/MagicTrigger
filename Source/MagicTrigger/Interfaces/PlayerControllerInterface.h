// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для класса PlayerControllerMagicTrigger. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "PlayerControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "PlayerControllerInterface")
class UPlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API IPlayerControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerControllerInterface")
		void SetInputRotationScale_IF(float mouseSensBaseValue, float mouseSensMultiplier, float mouseSensAddend);
};
