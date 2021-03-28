// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "SettingsMenuUserWidget.generated.h"

class UButton;
class USpacer;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API USettingsMenuUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget")
		UButton* ResumeButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget")
		UButton* BackMenuButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget")
		UButton* ControlButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget")
		USpacer* ResumeGameSpacer0;

public:
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
		void OnPressedBackMenuButton();
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
		void OnPressedResumeButton();
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
		void OnPressedControlButton();


};
