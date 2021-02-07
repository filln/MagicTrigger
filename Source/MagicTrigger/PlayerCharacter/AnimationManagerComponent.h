// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для взаимодействия между классом перса PlayerCharacterMagicTrigger и его классом анимаций AnimInstance (ABP_PlayerCharacter).
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MagicTrigger/Interfaces/AnimationManagerInterface.h"
#include "AnimationManagerComponent.generated.h"


class UAnimInstance;
class ACharacter;
class UAnimMontage;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Category = "AnimationManagerComponent")
class MAGICTRIGGER_API UAnimationManagerComponent : public UActorComponent, public IAnimationManagerInterface
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

	//Анимация готовности к атаке. Нужно определить в БП владельца компонента.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimationManagerComponent")
		UAnimMontage* FightIdleMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimationManagerComponent")
		float CheckStopJumpAnimationTimerRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimationManagerComponent")
		float CheckStopAttackAnimationTimerRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimationManagerComponent")
		float CheckStopThrowAnimationTimerRate;

protected:

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent")
		float PlayRateLiftingThrowingObject;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationManagerComponent")
		float StartPositionLiftingThrowingObject;

private:
	UAnimInstance* AnimInstance;
	AActor* Owner;
	ACharacter* PlayerCharacter;
	FTimerHandle CheckStopJumpAnimationTimer;
	FTimerHandle CheckStopAttackAnimationTimer;
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
		void AttackAnimation();
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


private:
	void CheckStopJumpAnimation();
	void CheckStopAttackAnimation();
	void CheckStopThrowAnimation();


	/**
	* AnimationManagerInterface methods.
	*/
public:
	/**
* AnimationManagerInterface methods.
*/
/**
 * Setters
 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetPlayingAnimationAttack_IF(bool bPlaying);
	virtual void SetPlayingAnimationAttack_IF_Implementation(bool bPlaying) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetPlayingAnimationThrow_IF(bool bPlaying);
	virtual void SetPlayingAnimationThrow_IF_Implementation(bool bPlaying) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetPlayingAnimationJump_IF(bool bPlaying);
	virtual void SetPlayingAnimationJump_IF_Implementation(bool bPlaying) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetPlayingAnimationLiftUp1Hand_IF(bool bPlaying);
	virtual void SetPlayingAnimationLiftUp1Hand_IF_Implementation(bool bPlaying) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetPlayingAnimationPutDown1Hand_IF(bool bPlaying);
	virtual void SetPlayingAnimationPutDown1Hand_IF_Implementation(bool bPlaying) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetPlayingAnimationLiftUp2Hand_IF(bool bPlaying);
	virtual void SetPlayingAnimationLiftUp2Hand_IF_Implementation(bool bPlaying) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetPlayingAnimationPutDown2Hand_IF(bool bPlaying);
	virtual void SetPlayingAnimationPutDown2Hand_IF_Implementation(bool bPlaying) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetGettingDamage_IF(bool bInGettingDamage);
	virtual void SetGettingDamage_IF_Implementation(bool bInGettingDamage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetCarrying_IF(bool bInCarrying);
	virtual void SetCarrying_IF_Implementation(bool bInCarrying) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Setters")
		void SetCanInteract_IF(bool bInCanInteract);
	virtual void SetCanInteract_IF_Implementation(bool bInCanInteract) override;

	/**
* AnimationManagerInterface methods.
*/
/**
 * Getters
 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		bool GetAttacking_IF() const;
	virtual bool GetAttacking_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		bool GetWatchingNow_IF() const;
	virtual bool GetWatchingNow_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		bool GetLiftingUp2Hands_IF() const;
	virtual bool GetLiftingUp2Hands_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		bool GetLiftingUp1Hand_IF() const;
	virtual bool GetLiftingUp1Hand_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		bool GetPutingDown1Hand_IF() const;
	virtual bool GetPutingDown1Hand_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		bool GetThrowing_IF() const;
	virtual bool GetThrowing_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		bool GetGettingDamage_IF() const;
	virtual bool GetGettingDamage_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		bool GetDying_IF() const;
	virtual bool GetDying_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		bool GetCarrying_IF() const;
	virtual bool GetCarrying_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		float GetPlayRateLiftingThrowingObject_IF() const;
	virtual float GetPlayRateLiftingThrowingObject_IF_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface|Getters")
		float GetStartPositionLiftingThrowingObject_IF() const;
	virtual float GetStartPositionLiftingThrowingObject_IF_Implementation() const override;



	/**
* AnimationManagerInterface methods.
*/
/**
 * Other methods.
 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface")
		void StartTraceAttackRightFoot_IF();
	virtual void StartTraceAttackRightFoot_IF_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface")
		void StopTraceAttackRightFoot_IF();
	virtual void StopTraceAttackRightFoot_IF_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface")
		void StartTraceAttackLeftFoot_IF();
	virtual void StartTraceAttackLeftFoot_IF_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface")
		void StopTraceAttackLeftFoot_IF();
	virtual void StopTraceAttackLeftFoot_IF_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface")
		void SpawnThrowableActor_IF();
	virtual void SpawnThrowableActor_IF_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface")
		void AttachThrowableActor_IF();
	virtual void AttachThrowableActor_IF_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface")
		void AttachLiftingActor_IF();
	virtual void AttachLiftingActor_IF_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface")
		void DetachLiftingActor_IF();
	virtual void DetachLiftingActor_IF_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerComponent|AnimationManagerInterface")
		void ReportNoise_IF();
	virtual void ReportNoise_IF_Implementation() override;


};
