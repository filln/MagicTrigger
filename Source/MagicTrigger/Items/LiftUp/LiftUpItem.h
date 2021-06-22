// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс поднимаемых и таскаемых предметов.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicTrigger\Interfaces\LiftUpItemInterface.h"
#include "MagicTrigger\Interfaces\InteractionInterface.h"
#include "MagicTrigger\Interfaces\BeginPlayInterface.h"
#include "TargetSelectionPlugin\Public\TargetSelectionInterface.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "LiftUpItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class APlayerCharacterMagicTrigger;

UCLASS()
class MAGICTRIGGER_API ALiftUpItem : public AActor,
	public ILiftUpItemInterface,
	public IInteractionInterface,
	public ITargetSelectionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALiftUpItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/**
	 * Variables
	 */
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
		APlayerCharacterMagicTrigger* PlayerCharacter;


	/**
	 * Methods
	 */
public:
	virtual void SetSimulatePhysics(bool bSimulate);


	/**
	 * Interface methods.
	 */
public:

	/**
	 * LiftingItemInterface
	 */
	virtual FName GetAttachSocket_IF_Implementation() const override;
	virtual void SetSimulatePhysics_IF_Implementation(bool bSimulate) override;

	/**
	 * InteractionInterface
	 */
	virtual FText GetInteractionText_IF_Implementation() const override;
	virtual void Interact_IF_Implementation(APlayerCharacterMagicTrigger* InPlayerCharacter) override;

	/**
	 * TargetSelectionInterface
	 */
	 /*Called from the actor when the actor begins to observe.*/
	virtual void IsObserved_Implementation() override;
	/*Called from the actor when the actor finishes observing.*/
	virtual void IsNotObserved_Implementation() override;

};
