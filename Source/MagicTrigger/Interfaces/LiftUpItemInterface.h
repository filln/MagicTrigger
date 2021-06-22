// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для класса LiftUpItem. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "LiftUpItemInterface.generated.h"

 // This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "LiftUpItemInterface")
class ULiftUpItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MAGICTRIGGER_API ILiftUpItemInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftUpItemInterface")
		FName GetAttachSocket_IF() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftUpItemInterface")
		void LiftUpItself_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftUpItemInterface")
		void PutDownItself_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftUpItemInterface")
		void PickUpItself_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftUpItemInterface")
		void SetSimulatePhysics_IF(bool bSimulate);

};
