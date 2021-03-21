// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "SavedGameUserWidget.generated.h"

class UCheckBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API USavedGameUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
	

public:
	UCheckBox* SavedGameCheckBox;
	UTextBlock* NameOfSavedGame;
};
