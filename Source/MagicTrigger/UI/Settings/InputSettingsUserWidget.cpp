// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "InputSettingsUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/TextBlock.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "MagicTrigger/CoreClasses/HUDMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/UI/CursorUserWidget.h"

UInputSettingsUserWidget::UInputSettingsUserWidget()
{
	HoveredColor = FLinearColor(FVector(1, 0.845292, 0.24044));
	UnHoveredColor = FLinearColor(FVector(1));
	bReadyToChangeKey = false;
	PressKeyText = FText::FromStringTable("/Game/MagicTrigger/Data/ST_InputSettings.ST_InputSettings", "PressKeyTip");
	if (PressKeyText.IsEmpty())
	{
		DEBUGMESSAGE("PressKeyText.IsEmpty()");
	}
	CurrentInputSettingsStruct = FInputSettingsStruct();
	DefaultNoneAxisKeyMapping = FInputAxisKeyMapping();
	DefaultNoneActionKeyMapping = FInputActionKeyMapping();
	DefaultNoneAxisKeyMapping.AxisName = FName(TEXT("DefaultNone"));
	DefaultNoneActionKeyMapping.ActionName = FName(TEXT("DefaultNone"));
	CurrentChoiceAxisKeyToChange = FInputAxisKeyMapping();
	CurrentChoiceActionKeyToChange = FInputActionKeyMapping();
	CurrentChoiceAxisKeyToChange = DefaultNoneAxisKeyMapping;
	CurrentChoiceActionKeyToChange = DefaultNoneActionKeyMapping;
	UnusedBindingKey = FKey(FName(TEXT("---")));

	FillKeyMappingArrays();
}

void UInputSettingsUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InputSettings = UInputSettings::GetInputSettings();
	if (!InputSettings)
	{
		//DEBUGMESSAGE("!InputSettings");
	}
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	HUDMagicTrigger = GetHUDMagicTrigger();
	FillCurrentInputSettingsStruct();
}

void UInputSettingsUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInputSettingsUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ShowActionKeysNamesMapping();
}

void UInputSettingsUserWidget::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
	Super::NativeTick(MovieSceneBlends, InDeltaTime);
	if (bReadyToChangeKey)
	{
		SetMouseLocation();
	}
}

FReply UInputSettingsUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (!bReadyToChangeKey)
	{
		return FReply::Handled();
	}
	//DEBUGSTRING(UKismetInputLibrary::Key_GetDisplayName(UKismetInputLibrary::GetKey(InKeyEvent)).ToString());
	FindActionToChange(UKismetInputLibrary::GetKey(InKeyEvent));
	ReleaseCursor();
	return FReply::Handled();
}

FReply UInputSettingsUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bReadyToChangeKey)
	{
		return FReply::Handled();
	}
	//DEBUGSTRING(UKismetInputLibrary::Key_GetDisplayName(UKismetInputLibrary::PointerEvent_GetEffectingButton(InMouseEvent)).ToString());
	FindActionToChange(UKismetInputLibrary::PointerEvent_GetEffectingButton(InMouseEvent));
	ReleaseCursor();
	return FReply::Handled();
}

FReply UInputSettingsUserWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bReadyToChangeKey)
	{
		return FReply::Handled();
	}
	const float WheelDelta = UKismetInputLibrary::PointerEvent_GetWheelDelta(InMouseEvent);
	if (WheelDelta == 1)
	{
		FindActionToChange(FKey(DefaultInputSettingsStruct.MouseScrollUpKeyName));
	}
	if (WheelDelta == -1)
	{
		FindActionToChange(FKey(DefaultInputSettingsStruct.MouseScrollDownKeyName));
	}
	//DEBUGFLOAT(WheelDelta);
	ReleaseCursor();
	return FReply::Handled();
}

void UInputSettingsUserWidget::SetHoveredColorToText(UTextBlock* InText)
{
	InText->SetColorAndOpacity(HoveredColor);
}

void UInputSettingsUserWidget::SetUnHoveredColorToText(UTextBlock* InText)
{
	InText->SetColorAndOpacity(UnHoveredColor);
}

void UInputSettingsUserWidget::ResetToDefaults()
{
	if (!InputSettings)
	{
		DEBUGMESSAGE("!InputSettings");
		return;
	}

	for (auto& CurrentAxis : CurrentAxisArray)
	{
		InputSettings->RemoveAxisMapping(*CurrentAxis);
	}
	for (auto& CurrentAction : CurrentActionArray)
	{
		InputSettings->RemoveActionMapping(*CurrentAction);
	}
	for (auto& DefaultAxis : DefaultAxisArray)
	{
		InputSettings->AddAxisMapping(*DefaultAxis);
	}
	for (auto& DefaultAction : DefaultActionArray)
	{
		InputSettings->AddActionMapping(*DefaultAction);
	}
	FillCurrentInputSettingsStruct();
	ShowActionKeysNamesMapping();
	InputSettings->ForceRebuildKeymaps();
}

/**
*ChangeKey
*/
void UInputSettingsUserWidget::ChangeMoveForwardKey()
{
	MoveForwardKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceAxisKeyToChange = CurrentInputSettingsStruct.MoveForwardKeyMapping;
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.MoveActForwardKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeMoveBackwardKey()
{
	MoveBackwardKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceAxisKeyToChange = CurrentInputSettingsStruct.MoveBackwardKeyMapping;
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.MoveActBackwardKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeMoveLeftKey()
{
	MoveLeftKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceAxisKeyToChange = CurrentInputSettingsStruct.MoveLeftKeyMapping;
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.MoveActLeftKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeMoveRightKey()
{
	MoveRightKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceAxisKeyToChange = CurrentInputSettingsStruct.MoveRightKeyMapping;
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.MoveActRightKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeAttackKey()
{
	AttackKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.AttackKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeAutoRunKey()
{
	AutoRunKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.AutoRunKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeInteractKey()
{
	InteractKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.InteractKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeJumpKey()
{
	JumpKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.JumpKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeMeleeAbilityKey()
{
	MeleeAbilityKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.MeleeAbilityKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeOffWatchingKey()
{
	OffWatchingKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.OffWatchingKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeRunKey()
{
	RunKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.RunKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeSevenfoldSphereAbilityKey()
{
	SevenfoldSphereAbilityKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.SevenfoldSphereAbilityKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeShortWalkingKey()
{
	ShortWalkingKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.ShortWalkingKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeShowGameMenuKey()
{
	ShowGameMenuKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.ShowGameMenuKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeThrowAbilityKey()
{
	ThrowAbilityKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.ThrowAbilityKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeWatchEnemiesKey()
{
	WatchEnemiesKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.WatchEnemiesKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeWatchOtherActorsKey()
{
	WatchOtherActorsKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.WatchOtherActorsKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeZoomDownKey()
{
	ZoomDownKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.ZoomDownKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::ChangeZoomUpKey()
{
	ZoomUpKeyMappingTextBlock->SetText(PressKeyText);
	CurrentChoiceActionKeyToChange = CurrentInputSettingsStruct.ZoomUpKeyMapping;
	HoldCursor();
}

void UInputSettingsUserWidget::FillKeyMappingArrays()
{
	CurrentAxisArray =
	{
		&CurrentInputSettingsStruct.MoveForwardKeyMapping,
		&CurrentInputSettingsStruct.MoveBackwardKeyMapping,
		&CurrentInputSettingsStruct.MoveRightKeyMapping,
		&CurrentInputSettingsStruct.MoveLeftKeyMapping
	};
	CurrentActionArray =
	{
		&CurrentInputSettingsStruct.AttackKeyMapping,
		&CurrentInputSettingsStruct.AutoRunKeyMapping,
		&CurrentInputSettingsStruct.InteractKeyMapping,
		&CurrentInputSettingsStruct.JumpKeyMapping,
		&CurrentInputSettingsStruct.MeleeAbilityKeyMapping,
		&CurrentInputSettingsStruct.OffWatchingKeyMapping,
		&CurrentInputSettingsStruct.RunKeyMapping,
		&CurrentInputSettingsStruct.SevenfoldSphereAbilityKeyMapping,
		&CurrentInputSettingsStruct.ShortWalkingKeyMapping,
		&CurrentInputSettingsStruct.ShowGameMenuKeyMapping,
		&CurrentInputSettingsStruct.ThrowAbilityKeyMapping,
		&CurrentInputSettingsStruct.WatchEnemiesKeyMapping,
		&CurrentInputSettingsStruct.WatchOtherActorsKeyMapping,
		&CurrentInputSettingsStruct.ZoomDownKeyMapping,
		&CurrentInputSettingsStruct.ZoomUpKeyMapping,
		&CurrentInputSettingsStruct.MoveActForwardKeyMapping,
		&CurrentInputSettingsStruct.MoveActBackwardKeyMapping,
		&CurrentInputSettingsStruct.MoveActRightKeyMapping,
		&CurrentInputSettingsStruct.MoveActLeftKeyMapping
	};
	DefaultAxisArray =
	{
		&DefaultInputSettingsStruct.MoveForwardKeyMapping,
		&DefaultInputSettingsStruct.MoveBackwardKeyMapping,
		&DefaultInputSettingsStruct.MoveRightKeyMapping,
		&DefaultInputSettingsStruct.MoveLeftKeyMapping
	};
	DefaultActionArray =
	{
		&DefaultInputSettingsStruct.AttackKeyMapping,
		&DefaultInputSettingsStruct.AutoRunKeyMapping,
		&DefaultInputSettingsStruct.InteractKeyMapping,
		&DefaultInputSettingsStruct.JumpKeyMapping,
		&DefaultInputSettingsStruct.MeleeAbilityKeyMapping,
		&DefaultInputSettingsStruct.OffWatchingKeyMapping,
		&DefaultInputSettingsStruct.RunKeyMapping,
		&DefaultInputSettingsStruct.SevenfoldSphereAbilityKeyMapping,
		&DefaultInputSettingsStruct.ShortWalkingKeyMapping,
		&DefaultInputSettingsStruct.ShowGameMenuKeyMapping,
		&DefaultInputSettingsStruct.ThrowAbilityKeyMapping,
		&DefaultInputSettingsStruct.WatchEnemiesKeyMapping,
		&DefaultInputSettingsStruct.WatchOtherActorsKeyMapping,
		&DefaultInputSettingsStruct.ZoomDownKeyMapping,
		&DefaultInputSettingsStruct.ZoomUpKeyMapping,
		&DefaultInputSettingsStruct.MoveActForwardKeyMapping,
		&DefaultInputSettingsStruct.MoveActBackwardKeyMapping,
		&DefaultInputSettingsStruct.MoveActRightKeyMapping,
		&DefaultInputSettingsStruct.MoveActLeftKeyMapping
	};
}

void UInputSettingsUserWidget::FillCurrentInputSettingsStruct()
{
	if (!InputSettings)
	{
		DEBUGMESSAGE("!InputSettings");
		return;
	}
	FillAxisKeysInCurrentInputSettingsStruct(CurrentInputSettingsStruct.MoveForwardKeyMapping.AxisName,
	                                         CurrentInputSettingsStruct.MoveForwardKeyMapping,
	                                         CurrentInputSettingsStruct.MoveBackwardKeyMapping);
	FillAxisKeysInCurrentInputSettingsStruct(CurrentInputSettingsStruct.MoveRightKeyMapping.AxisName,
	                                         CurrentInputSettingsStruct.MoveRightKeyMapping,
	                                         CurrentInputSettingsStruct.MoveLeftKeyMapping);
	for (auto CurrentAction : CurrentActionArray)
	{
		FillActionKeysInCurrentInputSettingsStruct(CurrentAction->ActionName, *CurrentAction);
	}
	CurrentInputSettingsStruct.MoveActForwardKeyMapping.Key = CurrentInputSettingsStruct.MoveForwardKeyMapping.Key;
	CurrentInputSettingsStruct.MoveActBackwardKeyMapping.Key = CurrentInputSettingsStruct.MoveBackwardKeyMapping.Key;
	CurrentInputSettingsStruct.MoveActRightKeyMapping.Key = CurrentInputSettingsStruct.MoveRightKeyMapping.Key;
	CurrentInputSettingsStruct.MoveActLeftKeyMapping.Key = CurrentInputSettingsStruct.MoveLeftKeyMapping.Key;
}

void UInputSettingsUserWidget::FillAxisKeysInCurrentInputSettingsStruct(FName InActionNameMapping,
                                                                        FInputAxisKeyMapping& InPositiveScaleAxisKeyMapping,
                                                                        FInputAxisKeyMapping& InNegativeScaleAxisKeyMapping)
{
	TArray<FInputAxisKeyMapping> OutMappings;
	InputSettings->GetAxisMappingByName(InActionNameMapping, OutMappings);
	for (auto OutMapping : OutMappings)
	{
		if (OutMapping.Key.IsMouseButton() || OutMapping.Key.IsGamepadKey())
		{
			continue;
		}
		if (OutMapping.Scale == 1)
		{
			InPositiveScaleAxisKeyMapping = OutMapping;
		}
		if (OutMapping.Scale == -1)
		{
			InNegativeScaleAxisKeyMapping = OutMapping;
		}
	}
}

void UInputSettingsUserWidget::FillActionKeysInCurrentInputSettingsStruct(FName InActionNameMapping, FInputActionKeyMapping& InActionKeyMapping)
{
	TArray<FInputActionKeyMapping> OutMappings;
	InputSettings->GetActionMappingByName(InActionNameMapping, OutMappings);
	if (OutMappings.Num() == 1)
	{
		InActionKeyMapping = OutMappings[0];
	}
}

void UInputSettingsUserWidget::ShowActionKeysNamesMapping()
{
	MoveForwardKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.MoveForwardKeyMapping.Key.GetDisplayName());
	MoveBackwardKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.MoveBackwardKeyMapping.Key.GetDisplayName());
	MoveRightKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.MoveRightKeyMapping.Key.GetDisplayName());
	MoveLeftKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.MoveLeftKeyMapping.Key.GetDisplayName());

	AttackKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.AttackKeyMapping.Key.GetDisplayName());
	AutoRunKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.AutoRunKeyMapping.Key.GetDisplayName());
	InteractKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.InteractKeyMapping.Key.GetDisplayName());
	JumpKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.JumpKeyMapping.Key.GetDisplayName());
	MeleeAbilityKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.MeleeAbilityKeyMapping.Key.GetDisplayName());
	OffWatchingKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.OffWatchingKeyMapping.Key.GetDisplayName());
	RunKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.RunKeyMapping.Key.GetDisplayName());
	SevenfoldSphereAbilityKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.SevenfoldSphereAbilityKeyMapping.Key.GetDisplayName());
	ShortWalkingKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.ShortWalkingKeyMapping.Key.GetDisplayName());
	ShowGameMenuKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.ShowGameMenuKeyMapping.Key.GetDisplayName());
	ThrowAbilityKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.ThrowAbilityKeyMapping.Key.GetDisplayName());
	WatchEnemiesKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.WatchEnemiesKeyMapping.Key.GetDisplayName());
	WatchOtherActorsKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.WatchOtherActorsKeyMapping.Key.GetDisplayName());
	ZoomDownKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.ZoomDownKeyMapping.Key.GetDisplayName());
	ZoomUpKeyMappingTextBlock->SetText(CurrentInputSettingsStruct.ZoomUpKeyMapping.Key.GetDisplayName());
}

void UInputSettingsUserWidget::HoldCursor()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		DEBUGMESSAGE("!World");
		return;
	}
	// HUDMagicTrigger->SetInputMode(EInputMode::EIM_GameAndUI, this);
	// InputPitchScale = HUDMagicTrigger->GetInputPitchScale();
	// InputYawScale = HUDMagicTrigger->GetInputYawScale();
	// InputRollScale = HUDMagicTrigger->GetInputRollScale();
	// HUDMagicTrigger->SetInputRotationScale(0.1, 0.1, 0.1);
	SetFocus();
	SetCursor(EMouseCursor::None);
	const FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(World);
	MouseLocationX = UKismetMathLibrary::FTrunc(ViewportSize.X / 2);
	MouseLocationY = UKismetMathLibrary::FTrunc(ViewportSize.Y / 2);
	bReadyToChangeKey = true;
}

void UInputSettingsUserWidget::ReleaseCursor()
{
	//DEBUGMESSAGE("ReleaseCursor");
	// HUDMagicTrigger->SetInputRotationScale(InputPitchScale, InputYawScale, InputRollScale);
	// HUDMagicTrigger->SetInputMode(EInputMode::EIM_UIOnly, this);
	bReadyToChangeKey = false;
	SetCursor(EMouseCursor::Default);
	//После перемещения курсор становится видимым.
	if (PlayerController)
	{
		PlayerController->SetMouseLocation(MouseLocationX + 1, MouseLocationY + 1);	
	}
}

void UInputSettingsUserWidget::SetMouseLocation()
{
	//DEBUGMESSAGE("HoldCursor");
	if (PlayerController)
	{
		PlayerController->SetMouseLocation(MouseLocationX, MouseLocationY);	
	}
}

void UInputSettingsUserWidget::FindActionToChange(FKey InKey)
{
	//Check
	if (!InputSettings)
	{
		//DEBUGMESSAGE("!InputSettings");
		ShowActionKeysNamesMapping();
		ResetSupportVariablesToDefault();
		return;
	}
	if (InKey.GetFName() == FName(TEXT("None")))
	{
		//DEBUGMESSAGE("InKey.GetFName() == None");
		ShowActionKeysNamesMapping();
		ResetSupportVariablesToDefault();
		return;
	}
	//Проверить, есть ли уже такие назначенные клавиши. Если есть, то переназначить их как UnusedBindingKey
	for (auto& CurrentAxis : CurrentAxisArray)
	{
		if (CurrentChoiceAxisKeyToChange == *CurrentAxis)
		{
			continue;
		}
		if ((*CurrentAxis).Key == InKey)
		{
			//DEBUGMESSAGE("This Key binding is already exist.")
			PlayAnimation(BindingExistTextBlockAnimation);
			InputSettings->RemoveAxisMapping(*CurrentAxis);
			(*CurrentAxis).Key = UnusedBindingKey;
			InputSettings->AddAxisMapping(*CurrentAxis);
			break;
		}
	}
	for (auto& CurrentAction : CurrentActionArray)
	{
		if (CurrentChoiceActionKeyToChange == *CurrentAction)
		{
			continue;
		}
		if ((*CurrentAction).Key == InKey)
		{
			//DEBUGMESSAGE("This Key binding is already exist.");
			PlayAnimation(BindingExistTextBlockAnimation);
			InputSettings->RemoveActionMapping(*CurrentAction);
			(*CurrentAction).Key = UnusedBindingKey;
			InputSettings->AddActionMapping(*CurrentAction);
			break;
		}
	}
	//
	
	if (CurrentChoiceAxisKeyToChange.Key != DefaultNoneAxisKeyMapping.Key)
	{
		InputSettings->RemoveAxisMapping(CurrentChoiceAxisKeyToChange);
		CurrentChoiceAxisKeyToChange.Key = InKey;
		InputSettings->AddAxisMapping(CurrentChoiceAxisKeyToChange);
	}
	if (CurrentChoiceActionKeyToChange.Key != DefaultNoneActionKeyMapping.Key)
	{
		InputSettings->RemoveActionMapping(CurrentChoiceActionKeyToChange);
		CurrentChoiceActionKeyToChange.Key = InKey;
		InputSettings->AddActionMapping(CurrentChoiceActionKeyToChange);
	}
	InputSettings->ForceRebuildKeymaps();
	FillCurrentInputSettingsStruct();
	ShowActionKeysNamesMapping();
	ResetSupportVariablesToDefault();
}

void UInputSettingsUserWidget::ResetSupportVariablesToDefault()
{
	CurrentChoiceAxisKeyToChange = DefaultNoneAxisKeyMapping;
	CurrentChoiceActionKeyToChange = DefaultNoneActionKeyMapping;
	CurrentTextBlock = nullptr;
}
