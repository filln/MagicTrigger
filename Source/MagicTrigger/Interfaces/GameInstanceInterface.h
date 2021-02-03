// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для класса GameInstanceMagicTrigger. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameInstanceInterface.generated.h"

class UPlayerStateSaveGame;

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
		UPlayerStateSaveGame* LoadGamesData_IF(FString NameOfLoadGame);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		GetGameSettingsStruct_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameInstanceInterface")
		void SetGameSettingsStruct_IF();
};
