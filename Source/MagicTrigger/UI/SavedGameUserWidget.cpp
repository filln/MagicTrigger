// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SavedGameUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"

void USavedGameUserWidget::OnCheckStateChangedSavedGameCheckBox(bool bChecked)
{
	this->HUDMagicTrigger->SwitchSavedGames(bChecked, this);
}
