// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс врагов.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagicTrigger\Data\EnemyToBehaviorTreeStruct.h"
#include "EnemyCharacterMagicTrigger.generated.h"

UCLASS()
class MAGICTRIGGER_API AEnemyCharacterMagicTrigger : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacterMagicTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	/**
	 * Variables
	 */
public:

	FEnemyToBehaviorTreeStruct EnemyToBehaviorTreeStruct;


	/**
	 * Methods
	 */
public:
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "EnemyCharacterMagicTrigger")
		void StartAttack();
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "EnemyCharacterMagicTrigger")
		void StopAttack();
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "EnemyCharacterMagicTrigger")
		void StopRoaring();


};
