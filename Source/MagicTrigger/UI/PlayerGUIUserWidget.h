// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Главный игровой виджет с канвас-панелью.
 */

#pragma once

#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "PlayerGUIUserWidget.generated.h"

class UPanelAbilityUserWidget;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UPlayerGUIUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
	

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PlayerGUIUserWidget")
		UPanelAbilityUserWidget* PanelAbilityUserWidget;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerGUIUserWidget")
		float GetLife();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerGUIUserWidget")
		FText GetTextLife();
};
