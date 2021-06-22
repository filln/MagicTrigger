// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для взаимодействия между классом перса PlayerCharacterMagicTrigger и его классом анимаций AnimInstance (ABP_PlayerCharacter).
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationManagerComponent.generated.h"


class UAnimInstance;
class ACharacter;
class UAnimMontage;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Category = "AnimationManagerComponent")
class MAGICTRIGGER_API UAnimationManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAnimationManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
protected:

	//Анимация готовности к атаке. Нужно определить в БП.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimationManagerComponent")
		UAnimMontage* FightIdleMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimationManagerComponent")
		float CheckStopJumpAnimationTimerRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimationManagerComponent")
		float CheckStopMeleeAttackAnimationTimerRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimationManagerComponent")
		float CheckStopThrowAnimationTimerRate;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bLiftingUp1Hand;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bLiftingUp2Hands;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bPutingDown1Hand;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bThrowing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bDying;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bGettingDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bWatchingNow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bCarrying;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bJumping;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|States")
		bool bShortWalk;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|CanDo")
		bool bCanJump;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|CanDo")
		bool bCanAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|CanDo")
		bool bCanThrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|CanDo")
		bool bCanInteract;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent|CanDo")
		bool bCanRun;

private:
	UPROPERTY()
		UAnimInstance* AnimInstance;
	UPROPERTY()
		ACharacter* PlayerCharacter;
	FTimerHandle CheckStopJumpAnimationTimer;
	FTimerHandle CheckStopMeleeAttackAnimationTimer;
	FTimerHandle CheckStopThrowAnimationTimer;


	/**
	 * Methods
	 */
public:

	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void StartJump();
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void StopJump();
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void MeleeAttackAnimation();
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void ThrowAnimation();

public:
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void SetPlayingAnimationThrow(bool bPlaying);
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void SetPlayingAnimationAttack(bool bPlaying);
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void SetPlayingAnimationJump(bool bPlaying);
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void SetPlayingAnimationLiftUp1Hand(bool bPlaying);
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void SetPlayingAnimationLiftUp2Hands(bool bPlaying);
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void SetPlayingAnimationPutDown1Hand(bool bPlaying);
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void SetPlayingAnimationPutDown2Hands(bool bPlaying);
	UFUNCTION(BlueprintCallable, Category = "AnimationManagerComponent")
		void StopAnimations();

};
