// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ControlUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Interfaces\PlayerControllerInterface.h"
#include "MagicTrigger\UI\Settings\SettingsMenuUserWidget.h"
#include "Kismet\KismetTextLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components\Slider.h"
#include "Components\TextBlock.h"
#include "GameFramework\PlayerController.h"

UControlUserWidget::UControlUserWidget()
{
	MouseSensSliderMultiplier = 2;
	MouseSensSliderAddend = 0.1;
	MouseSensitivity = 1.1;

}

FText UControlUserWidget::ConvertMouseSensToText()
{
	return UKismetTextLibrary::Conv_FloatToText(this->MouseSensitivity, ERoundingMode::HalfToEven, false, false, 1, 324, 0, 2);
}

void UControlUserWidget::SetSliderValue()
{
	if (!this->HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger");
		return;
	}
	if (!this->HUDMagicTrigger->PlayerController)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger->PlayerController");
		return;
	}
	if (!IsInterfaceImplementedBy<IPlayerControllerInterface>(this->HUDMagicTrigger->PlayerController))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerControllerInterface>(this->HUDMagicTrigger->PlayerController)");
		return;
	}

	this->MouseSensitivity = IPlayerControllerInterface::Execute_GetMouseSensitivity_IF(this->HUDMagicTrigger->PlayerController);

	if (this->MouseSensSliderMultiplier <= 0)
	{
		DEBUGMESSAGE("this->MouseSensSliderMultiplier <= 0");
		this->MouseSensSlider->SetValue(0);
	}

	float SliderValue =(this->MouseSensitivity - this->MouseSensSliderAddend) / this->MouseSensSliderMultiplier;
	this->MouseSensSlider->SetValue(SliderValue);
	MouseSensTextBlock2->SetText(ConvertMouseSensToText());
}
void UControlUserWidget::OnValueChangedMouseSensSlider(float Value)
{
	if (!this->HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger");
		return;
	}
	if (!this->HUDMagicTrigger->PlayerController)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger->PlayerController");
		return;
	}
	if (!IsInterfaceImplementedBy<IPlayerControllerInterface>(this->HUDMagicTrigger->PlayerController))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerControllerInterface>(this->HUDMagicTrigger->PlayerController)");
		return;
	}
	this->MouseSensitivity = Value * this->MouseSensSliderMultiplier + this->MouseSensSliderAddend;
	IPlayerControllerInterface::Execute_SetInputRotationScale_IF(this->HUDMagicTrigger->PlayerController, this->MouseSensitivity);
	MouseSensTextBlock2->SetText(ConvertMouseSensToText());
}

void UControlUserWidget::OnPressedResumeButton()
{
	if (!this->HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger");
		return;
	}
	this->HUDMagicTrigger->SetPauseGame(false, this);
}

void UControlUserWidget::OnPressedBackMenuButton()
{
	if (!this->HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger");
		return;
	}
	if (!this->HUDMagicTrigger->SettingsMenuUserWidget)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger->SettingsMenuUserWidget");
		return;
	}
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->SettingsMenuUserWidget);
}

