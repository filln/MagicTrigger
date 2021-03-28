// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\Data\GameSettingsStruct.h"
#include "GameInstanceMagicTrigger.generated.h"

class UPlayerStateSaveGame;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMagicTrigger")
		TSubclassOf<UPlayerStateSaveGame> SaveGameClass;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMagicTrigger")
		FString GamesListName;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMagicTrigger")
		UPlayerStateSaveGame* CurrentStateOfPlayersSaveGame;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GameInstanceMagicTrigger")
		FGameSettingsStruct GameSettingsStruct;

	/**
	 * Methods
	 */
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
		UPlayerStateSaveGame* LoadGamesData(const FString& NameOfLoadGame);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "GameInstanceMagicTrigger")
		void MainSaveGame(const FString& NameOfSaveGame);
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
		void MainDeleteGame(const FString& NameOfDeleteGame);

private:
	/**
	 *
	 */
	FString ReplaceSpecSymbols(const FString& NameOfSaveGame);
	/**
	 *
	 */
	bool SaveNameToGamesList(const FString& NameOfSaveGame);
	/**
	 *
	 */
	bool DeleteSaveGame(const FString& NameOfDeleteGame);
	/**
	 *
	 */
	bool DeleteNameFromGamesList(const FString& NameOfDeleteGame);
	/**
	 *
	 */
	FName GetNameOfCurrentLevel();
	/**
	 * 
	 */
	bool SaveCurrentGame(const FString& NameOfSaveGame);



	/**
	 * GameInstanceInterface methods
	 */
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		UPlayerStateSaveGame* LoadGamesData_IF(FString& NameOfLoadGame);
	virtual UPlayerStateSaveGame* LoadGamesData_IF_Implementation(FString& NameOfLoadGame) override;
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
		void LoadGamesList_IF(TArray<FString>& InGamesList);
	virtual void LoadGamesList_IF_Implementation(TArray<FString>& InGamesList) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void MainLoadGame_IF(FString& InNameOfLoadGame);
	virtual void MainLoadGame_IF_Implementation(FString& InNameOfLoadGame) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void MainSaveGame_IF(FString& InNameOfSaveGame);
	virtual void MainSaveGame_IF_Implementation(FString& InNameOfSaveGame) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void MainDeleteGame_IF(FString& InNameOfDeleteGame);
	virtual void MainDeleteGame_IF_Implementation(FString& InNameOfDeleteGame) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void BeginNewGame_IF();
	virtual void BeginNewGame_IF_Implementation() override;


};
