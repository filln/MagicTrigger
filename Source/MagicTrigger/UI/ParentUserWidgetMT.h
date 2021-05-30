// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Родительский класс всех виджетов проекта.
 */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParentUserWidgetMT.generated.h"

class AHUDMagicTrigger;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UParentUserWidgetMT : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ParentUserWidgetMT")
		AHUDMagicTrigger* HUDMagicTrigger;

public:

	UFUNCTION(BlueprintCallable, Category = "ParentUserWidgetMT")
		AHUDMagicTrigger* GetHUDMagicTrigger();


};
