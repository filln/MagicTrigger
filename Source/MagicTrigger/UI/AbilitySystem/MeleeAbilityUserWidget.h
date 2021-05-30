// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Виджет абилки ближнего боя.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "MeleeAbilityUserWidget.generated.h"

class UImage;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UMeleeAbilityUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MeleeAbilityUserWidget")
		UImage* IconImage;
};
