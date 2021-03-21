// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "SaveGameMenuUserWidget.generated.h"

class UListOfSavedGamesUserWidget;
class UImage;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API USaveGameMenuUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
	

public:
	UListOfSavedGamesUserWidget* ListOfSavedGamesUserWidget;
	UImage* ScreenShotOfCurrentSaveGame;
	UEditableTextBox* NameOfCurrentSaveGame;
};
