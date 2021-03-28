﻿// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "ListOfSavedGamesUserWidget.generated.h"

class UImage;
class UScrollBox;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UListOfSavedGamesUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ListOfSavedGamesUserWidget")
		UImage* ScreenShotImage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ListOfSavedGamesUserWidget")
		UScrollBox* ListOfSavedGamesScrollBox;
public:

	UFUNCTION(BlueprintCallable, Category = "ListOfSavedGamesUserWidget")
		void Refresh();

};
