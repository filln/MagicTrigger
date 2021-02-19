// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
* Режим движения перса.
 */

#pragma once

#include "MovementStatusEnum.generated.h"

UENUM(BlueprintType, Category = "MovementStatusEnum")
enum class EMovementStatus : uint8
{
	EMM_Stop			UMETA(DisplayName = "Stop"),
	EMM_ShortWalking	UMETA(DisplayName = "ShortWalking"),
	EMM_Walking			UMETA(DisplayName = "Walking"),
	EMM_Running			UMETA(DisplayName = "Running"),
	EMM_AutoRunning		UMETA(DisplayName = "AutoRunning")
};