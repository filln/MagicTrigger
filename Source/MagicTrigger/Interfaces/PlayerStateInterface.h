// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для класса PlayerStateMagicTrigger. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "MagicTrigger/Data/SaveGame/PlayerStateSaveGameStruct.h"
#include "PlayerStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "PlayerStateInterface")
class UPlayerStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API IPlayerStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * Getters
	 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetLife_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetMaxLife_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetDefence_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetDamage_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetMaxDefence_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetMaxDamage_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetMultiplierOfDamage_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		FPlayerStateSaveGameStruct GetBeginGameStates_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		FPlayerStateSaveGameStruct GetStates_IF() const;

	/**
	 * Setters
	 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetLife_IF(float Life);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetMaxLife_IF(float MaxLife);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetDefence_IF(float Defence);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetDamage_IF(float Damage);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetMaxDefence_IF(float MaxDefence);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetMaxDamage_IF(float MaxDamage);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetMultiplierOfDamage_IF(float MultiplierOfDamage);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetBeginGameStates_IF(FPlayerStateSaveGameStruct BeginGamePlayerState);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetStates_IF(FPlayerStateSaveGameStruct PlayerState);



};
