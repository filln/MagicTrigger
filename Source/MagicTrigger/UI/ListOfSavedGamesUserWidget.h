// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "ListOfSavedGamesUserWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UListOfSavedGamesUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
	

public:
	UImage* ScreenShotImage;

public:

	UFUNCTION(BlueprintCallable, Category = "ListOfSavedGamesUserWidget")
	void Refresh();

};
