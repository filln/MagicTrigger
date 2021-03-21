// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "MenuUserWidget.generated.h"

class UButton;
class USpacer;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UMenuUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
	


public:

	UButton* ResumeButton;
	UButton* SaveGameMenuButton;
	USpacer* SpacerSave;
};
