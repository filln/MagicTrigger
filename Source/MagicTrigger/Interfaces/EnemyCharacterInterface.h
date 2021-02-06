// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для класса EnemyCharacter. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "EnemyCharacterInterface.generated.h"

class AActor;
class UTexture2D;

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "EnemyCharacterInterface")
class UEnemyCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API IEnemyCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * Getters
	 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		AActor* GetEnemy_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		float GetLife_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		float GetMaxLife_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		UTexture2D* GetIcon_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		FText GetName_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		bool GetDying_IF() const;

	/**
	 * Other
	 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface")
		void StopFindPlayer_IF(); 
};
