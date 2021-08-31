// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "ControlUserWidget.generated.h"

class UButton;
class USpacer;
class USlider;
class UTextBlock;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UControlUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

public:
	UControlUserWidget();

	/**
	 * Variables
	 */
public:
	/**
	 * Множитель на входе нужен для согласования чувствительности с положением слайдера в ControlWidget.
	 Также для установки максимума чувствительности. Слагаемое на входе - для установки минимальной чувствительности при нулевом положении слайдера.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ControlUserWidget")
		float MouseSensSliderMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ControlUserWidget")
		float MouseSensSliderAddend;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ControlUserWidget")
		UButton* ResumeButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ControlUserWidget")
		UButton* BackMenuButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ControlUserWidget")
		USpacer* ResumeGameSpacer0;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ControlUserWidget")
		USlider* MouseSensSlider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ControlUserWidget")
		UTextBlock* MouseSensTextBlock2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ControlUserWidget")
		float MouseSensitivity;

	/**
	 * Methods
	 */
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControlUserWidget")
		FText ConvertMouseSensToText();
	UFUNCTION(BlueprintCallable, Category = "ControlUserWidget")
		void SetSliderValue();
	UFUNCTION(BlueprintCallable, Category = "ControlUserWidget")
		void OnPressedResumeButton();
	UFUNCTION(BlueprintCallable, Category = "ControlUserWidget")
		void OnPressedBackMenuButton();
	UFUNCTION(BlueprintCallable, Category = "ControlUserWidget")
		void OnValueChangedMouseSensSlider(float Value);

};
