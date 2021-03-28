// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "PlayerGUIUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UPlayerGUIUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerGUIUserWidget")
		float GetLife();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerGUIUserWidget")
		FText GetTextLife();
};
