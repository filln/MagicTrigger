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
	return UKismetTextLibrary::Conv_FloatToText(MouseSensitivity, ERoundingMode::HalfToEven, false, false, 1, 324, 0, 2);
}

void UControlUserWidget::SetSliderValue()
{
	if (!HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger");
		return;
	}
	if (!HUDMagicTrigger->PlayerController)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger->PlayerController");
		return;
	}
	if (!IsInterfaceImplementedBy<IPlayerControllerInterface>(HUDMagicTrigger->PlayerController))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerControllerInterface>(HUDMagicTrigger->PlayerController)");
		return;
	}

	MouseSensitivity = IPlayerControllerInterface::Execute_GetMouseSensitivity_IF(HUDMagicTrigger->PlayerController);

	if (MouseSensSliderMultiplier <= 0)
	{
		DEBUGMESSAGE("MouseSensSliderMultiplier <= 0");
		MouseSensSlider->SetValue(0);
	}

	float SliderValue =(MouseSensitivity - MouseSensSliderAddend) / MouseSensSliderMultiplier;
	MouseSensSlider->SetValue(SliderValue);
	MouseSensTextBlock2->SetText(ConvertMouseSensToText());
}
void UControlUserWidget::OnValueChangedMouseSensSlider(float Value)
{
	if (!HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger");
		return;
	}
	if (!HUDMagicTrigger->PlayerController)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger->PlayerController");
		return;
	}
	if (!IsInterfaceImplementedBy<IPlayerControllerInterface>(HUDMagicTrigger->PlayerController))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerControllerInterface>(HUDMagicTrigger->PlayerController)");
		return;
	}
	MouseSensitivity = Value * MouseSensSliderMultiplier + MouseSensSliderAddend;
	IPlayerControllerInterface::Execute_SetInputRotationScale_IF(HUDMagicTrigger->PlayerController, MouseSensitivity);
	MouseSensTextBlock2->SetText(ConvertMouseSensToText());
}

void UControlUserWidget::OnPressedResumeButton()
{
	if (!HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger");
		return;
	}
	HUDMagicTrigger->SetPauseGame(false, this);
}

void UControlUserWidget::OnPressedBackMenuButton()
{
	if (!HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger");
		return;
	}
	if (!HUDMagicTrigger->SettingsMenuUserWidget)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger->SettingsMenuUserWidget");
		return;
	}
	HUDMagicTrigger->SwitchWidgets(this, HUDMagicTrigger->SettingsMenuUserWidget);
}

