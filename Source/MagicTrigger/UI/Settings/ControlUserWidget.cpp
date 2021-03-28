// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ControlUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\Interfaces\PlayerControllerInterface.h"
#include "MagicTrigger\UI\Settings\SettingsMenuUserWidget.h"
#include "Kismet\KismetTextLibrary.h"
#include "Components\Slider.h"


UControlUserWidget::UControlUserWidget()
{
	MouseSensSliderMultiplier = 2;
	MouseSensSliderAddend = 0.1;
}

FText UControlUserWidget::GetMouseSens()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance)");
		return FText();
	}

	FGameSettingsStruct GameSettingsStruct = IGameInstanceInterface::Execute_GetGameSettingsStruct_IF(this->HUDMagicTrigger->GameInstance);
	float MouseSens = GameSettingsStruct.MouseSensitivity;
	return UKismetTextLibrary::Conv_FloatToText(MouseSens, ERoundingMode::HalfToEven, true, false, 1, 324, 0, 2);
}

void UControlUserWidget::SetMouseSens()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance)");
		return;
	}

	FGameSettingsStruct GameSettingsStruct = IGameInstanceInterface::Execute_GetGameSettingsStruct_IF(this->HUDMagicTrigger->GameInstance);
	float MouseSens = GameSettingsStruct.MouseSensitivity;

	if (this->MouseSensSliderMultiplier <= 0)
	{
		DEBUGMESSAGE("this->MouseSensSliderMultiplier <= 0");
		this->MouseSensSlider->SetValue(0);
	}

	float SliderValue =(MouseSens - this->MouseSensSliderAddend) / this->MouseSensSliderMultiplier;
	this->MouseSensSlider->SetValue(SliderValue);
}

void UControlUserWidget::OnPressedResumeButton()
{
	this->HUDMagicTrigger->SetPauseGame(false, this);
}

void UControlUserWidget::OnPressedBackMenuButton()
{
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->SettingsMenuUserWidget);
}

void UControlUserWidget::OnValueChangedMouseSensSlider(float Value)
{
	if (!IsInterfaceImplementedBy<IPlayerControllerInterface>(this->HUDMagicTrigger->PlayerController))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerControllerInterface>(this->HUDMagicTrigger->PlayerController)");
		return;
	}

	IPlayerControllerInterface::Execute_SetInputRotationScale_IF(this->HUDMagicTrigger->PlayerController, Value, this->MouseSensSliderMultiplier, this->MouseSensSliderAddend);
}
