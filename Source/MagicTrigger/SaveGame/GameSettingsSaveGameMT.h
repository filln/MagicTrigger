// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Для сохранения настроек игры.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSettingsSaveGameMT.generated.h"

 /**
  *
  */
UCLASS()
class MAGICTRIGGER_API UGameSettingsSaveGameMT : public USaveGame
{
	GENERATED_BODY()

public:
	UGameSettingsSaveGameMT();

	UPROPERTY(VisibleAnywhere, Category = "GameSettingsSaveGameMT")
		float MouseSensitivity;
};
