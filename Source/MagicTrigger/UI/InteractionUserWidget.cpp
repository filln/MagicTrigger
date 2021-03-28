// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "InteractionUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"

FText UInteractionUserWidget::GetInteractionText()
{
	return HUDMagicTrigger->InteractionText;
}
