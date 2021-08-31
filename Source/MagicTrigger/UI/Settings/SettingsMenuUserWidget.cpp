// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SettingsMenuUserWidget.h"
#include "MagicTrigger/CoreClasses/HUDMagicTrigger.h"
#include "MagicTrigger/UI/MenuUserWidget.h"
#include "MagicTrigger/UI/Settings/ControlUserWidget.h"

void USettingsMenuUserWidget::OnPressedBackMenuButton()
{
	HUDMagicTrigger->SwitchWidgets(this, HUDMagicTrigger->MenuUserWidget);
}

void USettingsMenuUserWidget::OnPressedResumeButton()
{
	HUDMagicTrigger->SetPauseGame(false, this);
}

void USettingsMenuUserWidget::OnPressedControlButton()
{
	HUDMagicTrigger->ControlUserWidget->SetSliderValue();
	HUDMagicTrigger->SwitchWidgets(this, HUDMagicTrigger->ControlUserWidget);
}
