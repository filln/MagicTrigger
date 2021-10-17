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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget")
	UButton* ResumeButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget")
	USpacer* ResumeGameSpacer0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
	UComboBoxString* ScreenResolutionComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
	UComboBoxString* ResolutionScaleComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
	UComboBoxString* ViewDistanceComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
	UComboBoxString* AntiAliasingComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
	UComboBoxString* PostProcessingComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
	UComboBoxString* ShadowsComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
	UComboBoxString* TexturesComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
	UComboBoxString* EffectsComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
	UComboBoxString* FoliageComboBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SettingsMenuUserWidget|ComboBox")
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
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
	void OnPressedBackMenuButton();
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
	void OnPressedResumeButton();

	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
	void ApplyGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
	void ResetToDefaultGraphicsSettings();

	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
	void LoadLowGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
	void LoadMediumGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
	void LoadHighGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
	void LoadEpicGraphicsSettings();
	UFUNCTION(BlueprintCallable, Category = "SettingsMenuUserWidget")
	void LoadCinematicGraphicsSettings();

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
