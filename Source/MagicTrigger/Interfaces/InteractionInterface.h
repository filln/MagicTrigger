// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для взаимодействия перса с объектами игры.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "InteractionInterface")
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractionInterface")
		FText GetInteractionText_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractionInterface")
		void Interact_IF();

};
