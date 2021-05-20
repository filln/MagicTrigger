// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс поднимаемых и таскаемых предметов.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicTrigger\Interfaces\LiftingItemInterface.h"
#include "MagicTrigger\Interfaces\InteractionInterface.h"
#include "MagicTrigger\Interfaces\BeginPlayInterface.h"
#include "TargetSelectionPlugin\Public\TargetSelectionInterface.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "LiftingItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class ACharacter;


UCLASS()
class MAGICTRIGGER_API ALiftingItem : public AActor,
	public ILiftingItemInterface,
	public IInteractionInterface,
	public ITargetSelectionInterface,
	public IBeginPlayInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALiftingItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LiftingItem|Components")
		UStaticMeshComponent* StaticMesh;
	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LiftingItem|Components")
		UBoxComponent* Box;
	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LiftingItem|Components")
		UBoxComponent* InteractCollision;

	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LiftingItem")
		FName AttachSocket;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LiftingItem")
		FText InteractionText;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LiftingItem")
		ACharacter* PlayerCharacter;

protected:
	FTimerHandle BeginPlayTimer;

	/**
	 * Interface methods.
	 */
public:

	/**
	 * LiftingItemInterface
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftingItemInterface")
		FName GetAttachSocket_IF() const;
	virtual FName GetAttachSocket_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftingItemInterface")
		void SetPlayingAnimationLiftUp_IF(bool bPlaying);
	virtual void SetPlayingAnimationLiftUp_IF_Implementation(bool bPlaying) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftingItemInterface")
		void SetPlayingAnimationPutDown_IF(bool bPlaying);
	virtual void SetPlayingAnimationPutDown_IF_Implementation(bool bPlaying) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftingItemInterface")
		void SetSimulatePhysics_IF(bool bSimulate);
	virtual void SetSimulatePhysics_IF_Implementation(bool bSimulate) override;

	/**
	 * InteractionInterface
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractionInterface")
		FText GetInteractionText_IF() const;
	virtual FText GetInteractionText_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractionInterface")
		void Interact_IF();
	virtual void Interact_IF_Implementation() override;

	/**
	 * TargetSelectionInterface
	 */
	 /*Called from the actor when the actor begins to observe.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TargetSelectionInterface")
		void IsObserved();
	virtual void IsObserved_Implementation() override;
	/*Called from the actor when the actor finishes observing.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TargetSelectionInterface")
		void IsNotObserved();
	virtual void IsNotObserved_Implementation() override;

	/**
	 * BeginplayInterface
	 */

	//Запустить BeginPlayTimer.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		void StartBeginPlayTimer_IF();
	virtual void StartBeginPlayTimer_IF_Implementation() override;

};
