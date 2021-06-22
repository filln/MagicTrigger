// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/*
Виджет абилки метания камня.
*/

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "ThrowAbilityUserWidget.generated.h"

class UImage;
class UTextBlock;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UThrowAbilityUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
public:

	UThrowAbilityUserWidget();

	/**
	 * Variables
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ThrowAbilityUserWidget")
		UImage* IconImage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ThrowAbilityUserWidget")
		UTextBlock* CountText;

	/**
	 * Methods
	 */
protected:

	virtual void NativeConstruct() override;
};
