// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\Data\GameSettingsStruct.h"
#include "GameInstanceMagicTrigger.generated.h"

class USaveGameMT;
class USaveGameManager;
class ULoadingUserWidget;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UGameInstanceMagicTrigger : public UGameInstance, public IGameInstanceInterface
{
	GENERATED_BODY()

public:
	UGameInstanceMagicTrigger();

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMagicTrigger")
		FString GamesListName;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMagicTrigger")
		FString GameSettingsName;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMagicTrigger")
		FGameSettingsStruct GameSettingsStruct;
	UPROPERTY()
		USaveGameManager* SaveGameManager;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMagicTrigger|Widgets")
		ULoadingUserWidget* LoadingUserWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMagicTrigger|Widgets")
		TSubclassOf<ULoadingUserWidget> LoadingUserWidgetClass;

	UPROPERTY()
		USaveGameMT* CurrentLoadingGame;
private:
	/**
	 * Показывает, что уровень загрузился. Меняется на true в левел-блюпринтах после загрузки стриминг-левелов.
	 */
	bool bLevelLoaded;
	/**
	 * Для ожидания загрузки уровня.
	 */
	FTimerHandle LoadingGameTimer;
	/**
	 *
	 */
	FTimerHandle BeginNewGameTimer;
	/**
	 *
	 */
	FTimerHandle ShowGameMenuTimer;
	/**
	 *
	 */


	/**
	 * Methods
	 */

protected:
	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init() override;
	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override;

public:
	/**
	 *Не используется?
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		bool LoadGamesNamesList(TArray<FString>& InSavedGamesNamesList);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		USaveGameMT* LoadGamesData(const FString& NameOfLoadGame);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		bool MainSaveGame(const FString& NameOfSaveGame, TArray<FString>& InGamesList);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		void MainLoadGame(const FString& NameOfLoadGame);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		void BeginNewGame();
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		bool MainDeleteGame(const FString& NameOfDeleteGame, TArray<FString>& InGamesList);
	/**
	 * Перенос настроек из виджетов в PlayerController и в сохранение. Вызывается, когда нажимаем кнопку "сохранить настройки".
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		void SaveGameSettings();
	/**
	 * Перенос настроек из сохранения в PlayerController и виджеты. Вызывается, когда заходим в игру.
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		void LoadGameSettings();
	/**
	 *Сброс настроек к дефолтным. переносятся все настройки из структуры FGameSettingsStruct в виджеты и PlayerController, применение настроек.
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		void ResetGameSettings();

	/**
	 *
	 */
	FName GetNameOfCurrentLevel();

	///**
	// *
	// */
	//UFUNCTION()
	//	void DoAfterBeginNewGame(AHUD* InHUD);
	///**
	// *
	// */
	//UFUNCTION()
	//	void DoAfterMainLoadGame(AHUD* InHUD, USaveGameMT* InLoadingGameTmp);

private:
	/**
	 *
	 */
	FString ReplaceSpecSymbols(const FString& NameOfSaveGame);
	/**
	 *
	 */
	bool SaveNameToGamesList(const FString& NameOfSaveGame, TArray<FString>& InGamesList);
	/**
	 *
	 */
	bool DeleteSaveGame(const FString& NameOfDeleteGame);
	/**
	 *
	 */
	bool DeleteNameFromGamesList(const FString& NameOfDeleteGame, TArray<FString>& InGamesList);
	/**
	 *
	 */
	bool SaveCurrentGame(const FString& NameOfSaveGame);


	/**
	 * GameInstanceInterface methods
	 */
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		USaveGameMT* LoadGamesData_IF(FString& NameOfLoadGame);
	virtual USaveGameMT* LoadGamesData_IF_Implementation(FString& NameOfLoadGame) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		FGameSettingsStruct GetGameSettingsStruct_IF() const;
	virtual FGameSettingsStruct GetGameSettingsStruct_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void SetGameSettingsStruct_IF(FGameSettingsStruct InGameSettingsStruct);
	virtual void SetGameSettingsStruct_IF_Implementation(FGameSettingsStruct InGameSettingsStruct) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void SetMouseSensitivity_IF(float MouseSensitivity);
	virtual void SetMouseSensitivity_IF_Implementation(float MouseSensitivity) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		bool LoadGamesList_IF(TArray<FString>& InGamesList);
	virtual bool LoadGamesList_IF_Implementation(TArray<FString>& InGamesList) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void MainLoadGame_IF(FString& InNameOfLoadGame);
	virtual void MainLoadGame_IF_Implementation(FString& InNameOfLoadGame) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		bool MainSaveGame_IF(FString& InNameOfSaveGame, TArray<FString>& InGamesList);
	virtual bool MainSaveGame_IF_Implementation(FString& InNameOfSaveGame, TArray<FString>& InGamesList) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		bool MainDeleteGame_IF(FString& InNameOfDeleteGame, TArray<FString>& InGamesList);
	virtual bool MainDeleteGame_IF_Implementation(FString& InNameOfDeleteGame, TArray<FString>& InGamesList) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void BeginNewGame_IF();
	virtual void BeginNewGame_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void SetLevelLoadedTrue_IF();
	virtual void SetLevelLoadedTrue_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void SaveGameSettings_IF();
	virtual void SaveGameSettings_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void ResetGameSettings_IF();
	virtual void ResetGameSettings_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void ShowGameMenu_IF();
	virtual void ShowGameMenu_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		FString GetGamesListName_IF();
	virtual FString GetGamesListName_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void ShowLoadingUserWidget_IF();
	virtual void ShowLoadingUserWidget_IF_Implementation() override;
};
