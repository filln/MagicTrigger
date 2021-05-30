// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Панель виджетов выбора абилок.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "PanelAbilityUserWidget.generated.h"

class UMeleeAbilityUserWidget;
class UThrowAbilityUserWidget;
class USFSphereAbilityUserWidget;
class UBorder;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UPanelAbilityUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
public:

	/**
	 * Variables
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		UBorder* MeleeBorder;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		UBorder* ThrowBorder;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		UBorder* SFSphereBorder;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		UMeleeAbilityUserWidget* MeleeAbilityUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		UThrowAbilityUserWidget* ThrowAbilityUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		USFSphereAbilityUserWidget* SFSphereAbilityUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		float ActiveAlpha;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		float InactiveAlpha;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		FLinearColor BorderColor;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		FLinearColor AbilityWidgetColorAndOpacity;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		FLinearColor ActiveBorderColor;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		FLinearColor InactiveBorderColor;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		FLinearColor ActiveAbilityWidgetColorAndOpacity;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PanelAbilityUserWidget")
		FLinearColor InactiveAbilityWidgetColorAndOpacity;

	/**
	 * Methods
	 */
	UFUNCTION(BlueprintCallable, Category = "PanelAbilityUserWidget")
		void SetActiveColor();
	UFUNCTION(BlueprintCallable, Category = "PanelAbilityUserWidget")
		void SetWidgetsColor();

};
