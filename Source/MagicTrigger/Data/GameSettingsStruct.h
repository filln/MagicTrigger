// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для настроек игры и их сохранения.
 */

#pragma once

#include "GameSettingsStruct.generated.h"

USTRUCT(BlueprintType)
struct FGameSettingsStruct
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameSettingsStruct")
		float MouseSensitivity;

	FGameSettingsStruct()
	{
		MouseSensitivity = 1.1f;
	}
};
