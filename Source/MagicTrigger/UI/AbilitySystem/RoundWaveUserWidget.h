// Copyright 2023 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/*
Виджет абилки волны.
*/

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "RoundWaveUserWidget.generated.h"

class UImage;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API URoundWaveUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

	/**
	* Variables
	*/
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "RoundWaveUserWidget")
	UImage* IconImage;


	/**
	 * Methods
	 */
};
