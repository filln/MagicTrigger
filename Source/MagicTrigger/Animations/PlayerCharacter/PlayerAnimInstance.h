// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Анимации для перса.
 */

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class UAnimationManagerComponent;
class APlayerCharacterMagicTrigger;
class APawn;
/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerAnimInstance|Components")
		UAnimationManagerComponent* AnimationManagerComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAnimInstance|Animations")
		UAnimMontage* PlayerFightIdle;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerAnimInstance")
		APlayerCharacterMagicTrigger* PlayerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bMoving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bShortWalk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bWatchingNow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bLiftingUp2Hands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bLiftingUp1Hand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bPutingDown1Hand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bThrowing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bGettingDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bDying;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bFightingIdle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bCarrying;

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
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void PutDownPickUpItem();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void LiftUpPickUpItem();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void EndAnimationLiftingCarryItem();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void EndAnimationLiftingPickUpItem();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void StartAnimationLiftingCarryItem();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void EndAnimationPutDownCarryItem();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void EndAnimationPutDownPickUpItem();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void LiftUpCarryItem();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void PutDownCarryItem();

	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|TraceAttack")
		void StartTraceAttackLeftFoot();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|TraceAttack")
		void StartTraceAttackRightFoot();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|TraceAttack")
		void StopTraceAttackLeftFoot();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|TraceAttack")
		void StopTraceAttackRightFoot();

	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void EndAttack();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void StartAnimationThrow();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void EndAnimationThrow();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void ThrowThrowableItem();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void EndAnimationHitReaction();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void EndAnimationJump();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void ReportNoise();



};
