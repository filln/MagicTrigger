// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 *Для настройки клавиш управления в игре.
 */
#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Data/InputSettingsStruct.h"
#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "InputSettingsUserWidget.generated.h"

class UTextBlock;
class UButton;
class UInputSettings;
class APlayerController;
class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UInputSettingsUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

	UInputSettingsUserWidget();
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	/**
	 *Variables
	 */

public:
	/**
	 *ActionKeyMappingTextBlock
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* MoveBackwardKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* MoveForwardKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* MoveLeftKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* MoveRightKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* AttackKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* AutoRunKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* InteractKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* JumpKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* MeleeAbilityKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* OffWatchingKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* RunKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* SevenfoldSphereAbilityKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* ShortWalkingKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* ShowGameMenuKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* ThrowAbilityKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* WatchEnemiesKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* WatchOtherActorsKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* ZoomDownKeyMappingTextBlock;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyMappingTextBlock")
	UTextBlock* ZoomUpKeyMappingTextBlock;

	/**
	 *ActionKeyButton
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* MoveForwardKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* MoveBackwardKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* MoveLeftKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* MoveRightKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* AttackKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* AutoRunKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* InteractKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* JumpKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* MeleeAbilityKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* OffWatchingKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* RunKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* SevenfoldSphereAbilityKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* ShortWalkingKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* ShowGameMenuKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* ThrowAbilityKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* WatchEnemiesKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* WatchOtherActorsKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* ZoomDownKeyButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|ActionKeyButton")
	UButton* ZoomUpKeyButton;

	/**
	 *Aniamtion
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="InputSettingsUserWidget|Aniamtion")
	UWidgetAnimation* BindingExistTextBlockAnimation;

private:
	FLinearColor HoveredColor;
	FLinearColor UnHoveredColor;

	const FInputSettingsStruct DefaultInputSettingsStruct = FInputSettingsStruct();
	FInputSettingsStruct CurrentInputSettingsStruct;
	TArray<FInputAxisKeyMapping*> CurrentAxisArray;
	TArray<FInputActionKeyMapping*> CurrentActionArray;
	TArray<const FInputAxisKeyMapping*> DefaultAxisArray;
	TArray<const FInputActionKeyMapping*> DefaultActionArray;

	bool bReadyToChangeKey;
	FText PressKeyText;
	FKey UnusedBindingKey;
	FInputAxisKeyMapping CurrentChoiceAxisKeyToChange;
	FInputActionKeyMapping CurrentChoiceActionKeyToChange;
	FInputAxisKeyMapping DefaultNoneAxisKeyMapping;
	FInputActionKeyMapping DefaultNoneActionKeyMapping;

	int MouseLocationX;
	int MouseLocationY;
	// float InputYawScale;
	// float InputPitchScale;
	// float InputRollScale;

public:
	UPROPERTY()
	UInputSettings* InputSettings;
	UPROPERTY()
	APlayerController* PlayerController;
	
	/**
	 *Methods
	 */
public:
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget")
	void SetHoveredColorToText(UTextBlock* InText);
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget")
	void SetUnHoveredColorToText(UTextBlock* InText);
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget")
	void ResetToDefaults();

	/**
	 *ChangeKey
	 */
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeMoveForwardKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeMoveBackwardKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeMoveLeftKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeMoveRightKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeAttackKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeAutoRunKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeInteractKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeJumpKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeMeleeAbilityKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeOffWatchingKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeRunKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeSevenfoldSphereAbilityKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeShortWalkingKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeShowGameMenuKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeThrowAbilityKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeWatchEnemiesKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeWatchOtherActorsKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeZoomDownKey();
	UFUNCTION(BlueprintCallable, Category="InputSettingsUserWidget|ChangeKey")
	void ChangeZoomUpKey();


private:
	void FillKeyMappingArrays();

	//FillCurrentInputSettingsStruct()
	void FillCurrentInputSettingsStruct();
	//FillCurrentInputSettingsStruct()
	void FillAxisKeysInCurrentInputSettingsStruct(FName InActionNameMapping,
	                                              FInputAxisKeyMapping& InPositiveScaleAxisKeyMapping,
	                                              FInputAxisKeyMapping& InNegativeScaleAxisKeyMapping);
	//FillCurrentInputSettingsStruct()
	void FillActionKeysInCurrentInputSettingsStruct(FName InActionNameMapping, FInputActionKeyMapping& InActionKeyMapping);

	/**
	 *Показать клавиши в виджете.
	 */
	void ShowActionKeysNamesMapping();
	void HoldCursor();
	void ReleaseCursor();
	void SetMouseLocation();
	void FindActionToChange(FKey InKey);
	void ResetSupportVariablesToDefault();
};
