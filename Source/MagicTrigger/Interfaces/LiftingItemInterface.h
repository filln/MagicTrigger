// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для класса LiftingItem. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LiftingItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "LiftingItemInterface")
class ULiftingItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API ILiftingItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftingItemInterface")
		FName GetAttachSocket_IF() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftingItemInterface")
		void SetPlayingAnimationLiftUp_IF(bool bPlaying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftingItemInterface")
		void SetPlayingAnimationPutDown_IF(bool bPlaying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftingItemInterface")
		void SetSimulatePhysics_IF(bool bSimulate);

};
