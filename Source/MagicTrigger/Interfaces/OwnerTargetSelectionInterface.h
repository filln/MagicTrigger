// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для актора-владельца компонента TargetSelectionComponent. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OwnerTargetSelectionInterface.generated.h"

class AActor;

 // This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "OwnerTargetSelectionInterface")
class UOwnerTargetSelectionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MAGICTRIGGER_API IOwnerTargetSelectionInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OwnerTargetSelectionInterface")
		void OffWatchingActors_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OwnerTargetSelectionInterface")
		void RemoveAndSwitchActors_IF(AActor* RemovingActor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OwnerTargetSelectionInterface")
		AActor* GetObservedActor_IF() const;

};
