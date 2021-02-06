// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для класса HUDMagicTrigger. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDInterface.generated.h"

class AActor;
class UUserWidget;

 // This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "HUDInterface")
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MAGICTRIGGER_API IHUDInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		void SetEnemy_IF(AActor* Enemy);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		AActor* GetEnemy_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		void HideLoadingWidget_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		void HideLoadGameMenuWidget_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		void HideMenuWidget_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		void ShowObserveEnemyWidget_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		void HideObserveEnemyWidget_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		void PauseOrUnpauseGame_IF(bool bPause, UUserWidget* HiddenWidget);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		void ShowInteractionWidget_IF(FText& InteractionText);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
		void HideInteractionWidget_IF();

};
