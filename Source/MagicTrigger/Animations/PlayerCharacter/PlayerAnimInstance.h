// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerAnimInstance")
		APawn* PawnOwner;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		float PlayRateLiftingThrowingObject;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		float StartPositionLiftingThrowingObject;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bMoving;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bShortWalk;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bWatchingNow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bLiftingUp2Hands;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bLiftingUp1Hand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bPutingDown1Hand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bThrowing;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bGettingDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bDying;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
		bool bFightingIdle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAnimInstance")
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
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|LiftUpPutDown")
		void PutDownThrowingObject();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|LiftUpPutDown")
		void LiftUpThrowingObject();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|LiftUpPutDown")
		void EndAnimationLiftingCarriedObject();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|LiftUpPutDown")
		void EndAnimationLiftingThrowingObject();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|LiftUpPutDown")
		void StartAnimationLiftingCarriedObject();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|LiftUpPutDown")
		void EndAnimationPutDownCarriedObject();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|LiftUpPutDown")
		void EndAnimationPutDownThrowingObject();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|LiftUpPutDown")
		void LiftUpCarriedObject();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|LiftUpPutDown")
		void PutDownCarriedObject();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|TraceAttack")
		void StartTraceAttackLeftFoot();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|TraceAttack")
		void StartTraceAttackRightFoot();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|TraceAttack")
		void StopTraceAttackLeftFoot();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies|TraceAttack")
		void StopTraceAttackRightFoot();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
		void EndAttack();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
		void EndAnimationThrow();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
		void ThrowObject();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
		void EndAnimationHitReaction();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
		void EndAnimationJump();
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
		void ReportNoise();



};
