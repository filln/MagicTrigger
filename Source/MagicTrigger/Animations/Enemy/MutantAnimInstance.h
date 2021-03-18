// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Анимации для мутанта.
 */

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MutantAnimInstance.generated.h"

class AMutantCharacter;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UMutantAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMutantAnimInstance();

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "MutantAnimInstance")
		AMutantCharacter* Mutant;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MutantAnimInstance")
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MutantAnimInstance")
		bool bAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MutantAnimInstance")
		bool bGettingDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MutantAnimInstance")
		bool bDying;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MutantAnimInstance")
		bool bStunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MutantAnimInstance")
		float DurationAnimationStunning;

	/**
	 * Methods
	 */

private:
	// Executed when begin play is called on the owning component
	virtual void NativeBeginPlay() override;
	/** Executed when the Animation is updated */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/**
	 * Получить и проверить ссылки.
	 */
	bool GetAndCheckReferences();

public:
	/**
	 * Methods for AnimNotifies.
	 */

	UFUNCTION(BlueprintCallable, Category = "MutantAnimInstance|AnimNotifies")
		void StopTraceAttackRightHand();
	UFUNCTION(BlueprintCallable, Category = "MutantAnimInstance|AnimNotifies")
		void StopTraceAttackLeftHand();
	UFUNCTION(BlueprintCallable, Category = "MutantAnimInstance|AnimNotifies")
		void StartTraceAttackRightHand();
	UFUNCTION(BlueprintCallable, Category = "MutantAnimInstance|AnimNotifies")
		void StartTraceAttackLeftHand();
	UFUNCTION(BlueprintCallable, Category = "MutantAnimInstance|AnimNotifies")
		void EndAnimationHitReaction();
	UFUNCTION(BlueprintCallable, Category = "MutantAnimInstance|AnimNotifies")
		void EndAnimationStunning();
	UFUNCTION()
	void DoAfterEndAnimationStunning();

};
