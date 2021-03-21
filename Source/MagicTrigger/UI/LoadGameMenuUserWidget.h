// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "LoadGameMenuUserWidget.generated.h"

class UListOfSavedGamesUserWidget;
class UButton;
class USpacer;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API ULoadGameMenuUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
	
public:
	UListOfSavedGamesUserWidget* ListOfSavedGamesUserWidget;
	UButton* ResumeButton;
	USpacer* ResumeGameSpacer0;

};
