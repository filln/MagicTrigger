// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Враг перса Мутант.
 */

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\Interfaces\TrowableRockResponseInterface.h"
#include "MutantCharacter.generated.h"

class UMeleeAttackComponent;
class UArrowComponent;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API AMutantCharacter : public AEnemyCharacterMagicTrigger,
	public ITrowableRockResponseInterface
{
	GENERATED_BODY()

public:

	AMutantCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MutantCharacter|Components")
		UMeleeAttackComponent* MeleeAttackComponent;
	/**
	 * Стрелка для направления трейса при мили атаке.
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "MutantCharacter|Components")
		UArrowComponent* ArrowRightHand;
	/**
	 * Стрелка для направления трейса при мили атаке.
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "MutantCharacter|Components")
		UArrowComponent* ArrowLeftHand;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MutantCharacter|Settings")
		FName ArrowRightHandSocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MutantCharacter|Settings")
		FName ArrowLeftHandSocketName;

public:

	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "MutantCharacter")
		void StartTraceAttack(bool bRightHand);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "MutantCharacter")
		void StopTraceAttack();
	/**
	 *
	 */
	UFUNCTION()
		void TraceAttack(bool bRightHand);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TrowableRockResponseInterface")
		void Stunning_IF();
	virtual void Stunning_IF_Implementation();
};
