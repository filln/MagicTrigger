// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Враг перса Демон.
 */

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacterMagicTrigger.h"
#include "DemonCharacter.generated.h"

class UFireBallComponent;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API ADemonCharacter : public AEnemyCharacterMagicTrigger
{
	GENERATED_BODY()

public:

	ADemonCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DemonCharacter|Components")
		UFireBallComponent* FireBallComponent;

	/**
	 *
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

	/**
	 * Создать файрбол.
	 */
	UFUNCTION(BlueprintCallable, Category = "DemonCharacter")
		void CreateFireBall();

	/**
	 * Переместить файрбол к персу.
	 */
	UFUNCTION(BlueprintCallable, Category = "DemonCharacter")
		void MoveFireBallToTarget();
};
