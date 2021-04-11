	// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для класса GameInstanceMagicTrigger. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "MagicTrigger/Data/GameSettingsStruct.h"
#include "GameInstanceInterface.generated.h"

class USaveGameMT;

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "GameInstanceInterface")
class UGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API IGameInstanceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		USaveGameMT* LoadGamesData_IF(FString& NameOfLoadGame);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		FGameSettingsStruct GetGameSettingsStruct_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void SetGameSettingsStruct_IF(FGameSettingsStruct GameSettingsStruct);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void SetMouseSensitivity_IF(float MouseSensitivity);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		bool LoadGamesList_IF(TArray<FString>& InGamesList);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void MainLoadGame_IF(FString& InNameOfLoadGame);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		bool MainSaveGame_IF(FString& InNameOfSaveGame, TArray<FString>& InGamesList);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		bool MainDeleteGame_IF(FString& InNameOfDeleteGame, TArray<FString>& InGamesList);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void BeginNewGame_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void SetLevelLoadedTrue_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void SaveGameSettings_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void ResetGameSettings_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void ShowGameMenu_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		FString GetGamesListName_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void ShowLoadingUserWidget_IF();


};	
