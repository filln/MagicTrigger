// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "ControlUserWidget.generated.h"

class UButton;
class USpacer;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UControlUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

public:
	UButton* ResumeButton;
	USpacer* ResumeGameSpacer0;
	
};
