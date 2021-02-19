// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для взаимодействия с AnimationManager
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "AnimationManagerInterface.generated.h"

class UActorComponent;

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "AnimationManagerInterface")
class UAnimationManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API IAnimationManagerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * Setters
	 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationAttack_IF(bool bPlaying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationThrow_IF(bool bPlaying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationJump_IF(bool bPlaying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationLiftUp1Hand_IF(bool bPlaying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationPutDown1Hand_IF(bool bPlaying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationLiftUp2Hand_IF(bool bPlaying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationPutDown2Hand_IF(bool bPlaying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetGettingDamage_IF(bool bGettingDamage);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetCarrying_IF(bool bCarrying);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetCanInteract_IF(bool bCanInteract);

	/**
	 * Getters
	 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		bool GetAttacking_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		bool GetWatchingNow_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		bool GetLiftingUp2Hands_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		bool GetLiftingUp1Hand_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		bool GetPutingDown1Hand_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		bool GetThrowing_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		bool GetGettingDamage_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		bool GetDying_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		bool GetCarrying_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		float GetPlayRateLiftingThrowingObject_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		float GetStartPositionLiftingThrowingObject_IF() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		UActorComponent* GetAnimationManagerComponent_IF() const;

	/**
	 * Other methods.
	 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void StartTraceAttackRightFoot_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void StopTraceAttackRightFoot_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void StartTraceAttackLeftFoot_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void StopTraceAttackLeftFoot_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void SpawnThrowableActor_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void AttachThrowableActor_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void AttachLiftingActor_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void DetachLiftingActor_IF();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void ReportNoise_IF();

};
