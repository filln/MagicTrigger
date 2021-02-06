// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для реакции объекта на попадание метаемого камня. 
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "TrowableRockResponseInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "TrowableRockResponseInterface")  
class UTrowableRockResponseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API ITrowableRockResponseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TrowableRockResponseInterface")
		void Stunning_IF();
};
