// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 *Настройки графики.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "MagicTrigger/Data/Settings/GraphicsSettingsStruct.h"
#include "GraphicsSettingsUserWidget.generated.h"

class UButton;
class USpacer;
class UComboBoxString;
class UGameUserSettings;
class UCheckBox;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UGraphicsSettingsUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

	UGraphicsSettingsUserWidget();
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	/**
	 *Variables
	 */
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget")
	UButton* ResumeButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget")
	USpacer* ResumeGameSpacer0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget")
	UCheckBox* WindowedCheckBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* ScreenResolutionComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* ResolutionScaleComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* ViewDistanceComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* AntiAliasingComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* PostProcessingComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* ShadowsComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* TexturesComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* EffectsComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* FoliageComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GraphicsSettingsUserWidget|ComboBox")
	UComboBoxString* ShadingComboBox;
	
	UPROPERTY()
	UGameUserSettings* GameUserSettings;
	
private:
	FGraphicsSettingsStruct GraphicsSettingsStruct;
	TArray<FString*> ResolutionsArray;
	TArray<UComboBoxString*> LevelComboBoxes;
	TMap<FString, int32> GraphicsLevelsMap;
	bool bDisallowFillComboBoxes;

	/**
	 *Methods
	 */
public:
	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void OnPressedBackMenuButton();
	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void OnPressedResumeButton();

	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void ApplyGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void ResetToDefaultGraphicsSettings();

	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void LoadLowGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void LoadMediumGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void LoadHighGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void LoadEpicGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void LoadCinematicGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "GraphicsSettingsUserWidget")
	void SetWindowedMode(bool bInWindowedOn);

	private:
	void FillAllComboBox();
	void FillGraphicsLevelComboBox(UComboBoxString* InComboBox);
	void FillArraysFromGraphicSettingsStruct();
	void LoadSettingsFromSavedToWidget();
	void LoadSettingsFromSavedToComboBoxesBasedOnSwitch(int32 InLevel, UComboBoxString* InComboBox);
	void SaveSettingsFromWidget();
	FIntPoint ConvertResolutionStringToFIntPoint(const FString InResolution);
	FString ConvertFIntPointToResolutionString(const FIntPoint InResolution);
};
