// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "PanelAbilityUserWidget.h"
#include "Components/Border.h"
#include "MagicTrigger/UI/AbilitySystem/MeleeAbilityUserWidget.h"
#include "MagicTrigger/UI/AbilitySystem/ThrowAbilityUserWidget.h"
#include "MagicTrigger/UI/AbilitySystem/SFSphereAbilityUserWidget.h"
#include "MagicTrigger/UI/AbilitySystem/RoundWaveUserWidget.h"

void UPanelAbilityUserWidget::SetActiveColor()
{
	ActiveBorderColor = BorderColor;
	ActiveBorderColor.A = ActiveAlpha;
	InactiveBorderColor = BorderColor;
	InactiveBorderColor.A = InactiveAlpha;

	ActiveAbilityWidgetColorAndOpacity = AbilityWidgetColorAndOpacity;
	ActiveAbilityWidgetColorAndOpacity.A = ActiveAlpha;
	InactiveAbilityWidgetColorAndOpacity = AbilityWidgetColorAndOpacity;
	InactiveAbilityWidgetColorAndOpacity.A = InactiveAlpha;
}

void UPanelAbilityUserWidget::SetWidgetsColor()
{
	MeleeBorder->SetBrushColor(ActiveBorderColor);
	ThrowBorder->SetBrushColor(InactiveBorderColor);
	SFSphereBorder->SetBrushColor(InactiveBorderColor);
	RoundWaveBorder->SetBrushColor(InactiveBorderColor);

	MeleeAbilityUserWidget->SetColorAndOpacity(ActiveAbilityWidgetColorAndOpacity);
	ThrowAbilityUserWidget->SetColorAndOpacity(InactiveAbilityWidgetColorAndOpacity);
	SFSphereAbilityUserWidget->SetColorAndOpacity(InactiveAbilityWidgetColorAndOpacity);
	RoundWaveUserWidget->SetColorAndOpacity(InactiveAbilityWidgetColorAndOpacity);

}
