// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SettingsMenuUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\UI\MenuUserWidget.h"
#include "MagicTrigger\UI\Settings\ControlUserWidget.h"


void USettingsMenuUserWidget::OnPressedBackMenuButton()
{
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->MenuUserWidget);
}

void USettingsMenuUserWidget::OnPressedResumeButton()
{
	this->HUDMagicTrigger->SetPauseGame(false, this);
}

void USettingsMenuUserWidget::OnPressedControlButton()
{
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->ControlUserWidget);
}
