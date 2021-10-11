// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
* Для сохранения дефолтных настроек клавиш управления.
*/

#pragma once

#include "GameFramework/PlayerInput.h"
#include "InputSettingsStruct.generated.h"

USTRUCT(BlueprintType)
struct FInputSettingsStruct
{
	GENERATED_BODY()

	/**
	*ActionKeysMapping
	*/
	FInputAxisKeyMapping MoveForwardKeyMapping;
	FInputAxisKeyMapping MoveBackwardKeyMapping;
	FInputAxisKeyMapping MoveRightKeyMapping;
	FInputAxisKeyMapping MoveLeftKeyMapping;
	FInputActionKeyMapping AttackKeyMapping;
	FInputActionKeyMapping AutoRunKeyMapping;
	FInputActionKeyMapping InteractKeyMapping;
	FInputActionKeyMapping JumpKeyMapping;
	FInputActionKeyMapping MeleeAbilityKeyMapping;
	FInputActionKeyMapping OffWatchingKeyMapping;
	FInputActionKeyMapping RunKeyMapping;
	FInputActionKeyMapping SevenfoldSphereAbilityKeyMapping;
	FInputActionKeyMapping ShortWalkingKeyMapping;
	FInputActionKeyMapping ShowGameMenuKeyMapping;
	FInputActionKeyMapping ThrowAbilityKeyMapping;
	FInputActionKeyMapping WatchEnemiesKeyMapping;
	FInputActionKeyMapping WatchOtherActorsKeyMapping;
	FInputActionKeyMapping ZoomDownKeyMapping;
	FInputActionKeyMapping ZoomUpKeyMapping;

	FInputActionKeyMapping MoveActForwardKeyMapping;
	FInputActionKeyMapping MoveActBackwardKeyMapping;
	FInputActionKeyMapping MoveActRightKeyMapping;
	FInputActionKeyMapping MoveActLeftKeyMapping;

	/**
	*Mapping Names
	*/
	FName TurnNameMapping;
	FName LookUpNameMapping;

	/**
	 *Key Names
	 */
	FName MouseScrollUpKeyName;
	FName MouseScrollDownKeyName;

	FInputSettingsStruct()
	{
		
		/**
		*Mapping Names
		*/
		TurnNameMapping = FName(TEXT("Turn"));
		LookUpNameMapping = FName(TEXT("LookUp"));

		/**
		*Key Names
		*/
		MouseScrollUpKeyName = FName(TEXT("MouseScrollUp"));
		MouseScrollDownKeyName = FName(TEXT("MouseScrollDown"));
		
		/**
		*Action Names
		*/
		MoveForwardKeyMapping.AxisName = FName(TEXT("MoveForward"));
		MoveBackwardKeyMapping.AxisName = FName(TEXT("MoveForward"));
		MoveRightKeyMapping.AxisName = FName(TEXT("MoveRight"));
		MoveLeftKeyMapping.AxisName = FName(TEXT("MoveRight"));

		AttackKeyMapping.ActionName = FName(TEXT("Attack"));
		AutoRunKeyMapping.ActionName = FName(TEXT("AutoRun"));
		InteractKeyMapping.ActionName = FName(TEXT("Interact"));
		JumpKeyMapping.ActionName = FName(TEXT("Jump"));
		MeleeAbilityKeyMapping.ActionName = FName(TEXT("MeleeAbility"));
		OffWatchingKeyMapping.ActionName = FName(TEXT("OffWatchingActors"));
		RunKeyMapping.ActionName = FName(TEXT("Running"));
		SevenfoldSphereAbilityKeyMapping.ActionName = FName(TEXT("SSphereAbility"));
		ShortWalkingKeyMapping.ActionName = FName(TEXT("ShortWalking"));
		ShowGameMenuKeyMapping.ActionName = FName(TEXT("ShowGameMenu"));
		ThrowAbilityKeyMapping.ActionName = FName(TEXT("ThrowAbility"));
		WatchEnemiesKeyMapping.ActionName = FName(TEXT("WatchEnemies"));
		WatchOtherActorsKeyMapping.ActionName = FName(TEXT("WatchOtherActors"));
		ZoomDownKeyMapping.ActionName = FName(TEXT("ZoomDown"));
		ZoomUpKeyMapping.ActionName = FName(TEXT("ZoomUp"));

		MoveActForwardKeyMapping.ActionName = FName(TEXT("MoveAct"));
		MoveActBackwardKeyMapping.ActionName = FName(TEXT("MoveAct"));
		MoveActRightKeyMapping.ActionName = FName(TEXT("MoveAct"));
		MoveActLeftKeyMapping.ActionName = FName(TEXT("MoveAct"));

		/**
		 *Keys
		 */
		MoveForwardKeyMapping.Key = FKey(TEXT("W"));
		MoveBackwardKeyMapping.Key = FKey(TEXT("S"));
		MoveRightKeyMapping.Key = FKey(TEXT("D"));
		MoveLeftKeyMapping.Key = FKey(TEXT("A"));

		AttackKeyMapping.Key = FKey(TEXT("LeftMouseButton"));
		AutoRunKeyMapping.Key = FKey(TEXT("NumLock"));
		InteractKeyMapping.Key = FKey(TEXT("RightMouseButton"));
		JumpKeyMapping.Key = FKey(TEXT("SpaceBar"));
		MeleeAbilityKeyMapping.Key = FKey(TEXT("One"));
		OffWatchingKeyMapping.Key = FKey(TEXT("CapsLock"));
		RunKeyMapping.Key = FKey(TEXT("LeftShift"));
		SevenfoldSphereAbilityKeyMapping.Key = FKey(TEXT("Three"));
		ShortWalkingKeyMapping.Key = FKey(TEXT("LeftControl"));
		ShowGameMenuKeyMapping.Key = FKey(TEXT("Escape"));
		ThrowAbilityKeyMapping.Key = FKey(TEXT("Two"));
		WatchEnemiesKeyMapping.Key = FKey(TEXT("Tab"));
		WatchOtherActorsKeyMapping.Key = FKey(TEXT("Q"));
		ZoomDownKeyMapping.Key = FKey(MouseScrollDownKeyName);
		ZoomUpKeyMapping.Key = FKey(MouseScrollUpKeyName);

		MoveActForwardKeyMapping.Key = MoveForwardKeyMapping.Key;
		MoveActBackwardKeyMapping.Key = MoveBackwardKeyMapping.Key;
		MoveActRightKeyMapping.Key = MoveRightKeyMapping.Key;
		MoveActLeftKeyMapping.Key = MoveLeftKeyMapping.Key;

		/**
		 *Scales
		 */
		MoveBackwardKeyMapping.Scale = -1;
		MoveLeftKeyMapping.Scale = -1;

	}
};

// enum class EInputSettings : uint8
// {
// 	EIS_MoveForwardKeyMapping,
// 	EIS_MoveBackwardKeyMapping,
// 	EIS_MoveRightKeyMapping,
// 	EIS_MoveLeftKeyMapping,
// 	EIS_AttackKeyMapping,
// 	EIS_AutoRunKeyMapping,
// 	EIS_InteractKeyMapping,
// 	EIS_JumpKeyMapping,
// 	EIS_MeleeAbilityKeyMapping,
// 	EIS_OffWatchingKeyMapping,
// 	EIS_RunKeyMapping,
// 	EIS_SevenfoldSphereAbilityKeyMapping,
// 	EIS_ShortWalkingKeyMapping,
// 	EIS_ShowGameMenuKeyMapping,
// 	EIS_ThrowAbilityKeyMapping,
// 	EIS_WatchEnemiesKeyMapping,
// 	EIS_WatchOtherActorsKeyMapping,
// 	EIS_ZoomDownKeyMapping,
// 	EIS_ZoomUpKeyMapping,
// 	EIS_Default
// };
