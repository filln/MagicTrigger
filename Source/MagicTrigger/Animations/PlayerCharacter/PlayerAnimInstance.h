// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Анимации для перса.
 */

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class UActorComponent;

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
		UActorComponent* AnimationManagerComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAnimInstance|Animations")
		UAnimMontage* PlayerFightIdle;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerAnimInstance")
		APawn* PawnOwner;
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
		void PutDownThrowingObject();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void LiftUpThrowingObject();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void EndAnimationLiftingCarriedObject();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void EndAnimationLiftingThrowingObject();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void StartAnimationLiftingCarriedObject();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void EndAnimationPutDownCarriedObject();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void EndAnimationPutDownThrowingObject();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void LiftUpCarriedObject();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies|LiftUpPutDown")
		void PutDownCarriedObject();

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
		void EndAnimationThrow();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void ThrowObject();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void EndAnimationHitReaction();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void EndAnimationJump();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance|AnimNotifies")
		void ReportNoise();



};
