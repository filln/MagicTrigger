// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
* Текущая выбранная абилка.
 */

#pragma once

#include "CurrentAbilityEnum.generated.h"

UENUM(BlueprintType, Category = "CurrentAbilityEnum")
enum class ECurrentAbility : uint8
{
	ECA_Melee				UMETA(DisplayName = "Melee"),

	ECA_Throw				UMETA(DisplayName = "Throw"),

	ECA_SFSphere			UMETA(DisplayName = "SFSphere")

};