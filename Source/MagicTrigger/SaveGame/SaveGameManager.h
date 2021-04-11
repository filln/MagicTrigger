// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Для сбора данных из акторов при сохранении игры и для загрузки игры.
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MagicTrigger\Data\GameSettingsStruct.h"
#include "SaveGameManager.generated.h"

class UGameInstanceMagicTrigger;
class APlayerCharacterMagicTrigger;
class APlayerStateMagicTrigger;
class APlayerControllerMagicTrigger;
class AHUDMagicTrigger;
class USaveGameMT;
class UGameSettingsSaveGameMT;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API USaveGameManager : public UObject
{
	GENERATED_BODY()

public:
	USaveGameManager();

	/**
	 * Variables
	 */
public:
	UGameInstanceMagicTrigger* GameInstance;
	APlayerCharacterMagicTrigger* PlayerCharacter;
	APlayerStateMagicTrigger* PlayerState;
	APlayerControllerMagicTrigger* PlayerController;
	AHUDMagicTrigger* HUD;

private:
	float AllTimersDeltaTime;
	FTimerHandle LoadAllTimer;
	FTimerHandle LoadSettingsTimer;
	FTimerHandle HUDTimer;
	FTimerHandle PlayerCharacterTimer;
	FTimerHandle PlayerStateTimer;
	/**
	 * Количество, счетчик загруженных элементов. При загрузке игры каждый метод загрузки проверяет своим таймером данные на валидность
	 * и делает загрузку. После успеха каждый метод увеличивает этот счетчик на 1. В методе LoadAll таймер проверяет по этому счетчику, что все данные загрузились
	 * и можно скрывать виджет загрузки.
	 */
	size_t CountOfLoadedElements;
	/**
	 * Равен количеству подметодов метода LoadAll;
	 */
	const size_t MaxCountOfLoadedElements = 3;
	/**
	 * Methods
	 */
public:
	void LoadAll(USaveGameMT* InLoadingGame);
	void SaveAll(USaveGameMT* InSavingGame);
	/**
	 * Перенос настроек из сохранения в PlayerController и виджеты. Вызывается, когда заходим в игру.
	 */
	void LoadGameSettings(UGameSettingsSaveGameMT* InLoadingGame);
	/**
	 * Перенос настроек из виджетов в PlayerController и в сохранение. Вызывается, когда нажимаем кнопку "сохранить настройки".
	 */
	void SaveGameSettings(UGameSettingsSaveGameMT* InSavingGame);
	/**
	 *Сброс настроек к дефолтным. переносятся все настройки из структуры FGameSettingsStruct в виджеты и PlayerController, применение настроек.
	 */
	void ResetGameSettings();

	void SaveLevelName(USaveGameMT* InSavingGame);

private:

	void CheckHUD();
	void LoadPlayerCharacter(USaveGameMT* InLoadingGame);
	void SavePlayerCharacter(USaveGameMT* InSavingGame);

	void LoadPlayerState(USaveGameMT* InLoadingGame);
	void SavePlayerState(USaveGameMT* InSavingGame);

};
