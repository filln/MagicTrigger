// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
* Режим ввода игрока.
 */

#pragma once

#include "InputModeEnum.generated.h"

UENUM(BlueprintType, Category = "InputModeEnum")
enum class EInputMode : uint8
{
    EIM_UIOnly      UMETA(DisplayName = "UI_Only"),
    EIM_GameOnly    UMETA(DisplayName = "Game_Only")

};