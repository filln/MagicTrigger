// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс метаемых предметов.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger\Items\LiftingItem.h"
#include "ThrowableItem.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;
class UStaticMeshComponent;
class APlayerCharacterMagicTrigger;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API AThrowableItem : public AActor,
	public IInteractionInterface,
	public ITargetSelectionInterface
{
	GENERATED_BODY()

public:
	AThrowableItem();

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
		APlayerCharacterMagicTrigger* PlayerCharacter;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "ThrowableItem|Components")
		UProjectileMovementComponent* ProjectileMovementComponent;
	/**
	 * Параметр для UGameplayStatics::SuggestProjectileVelocity_CustomArc(), определяет дугу полета. Только если известна цель.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThrowableItem|Settings")
		float ArcParam;
	/**
	 * Скорость камня, если нет цели.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThrowableItem|Settings")
		float Speed;
	/**
	 * Крутизна дуги, если нет цели.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThrowableItem|Settings")
		float ArcAlpha;
	/**
	 * 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThrowableItem|Settings")
		float Damage;

public:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	/**
	 * InteractionInterface
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractionInterface")
		FText GetInteractionText_IF() const;
	virtual FText GetInteractionText_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractionInterface")
		void Interact_IF(APlayerCharacterMagicTrigger* InPlayerCharacter);
	virtual void Interact_IF_Implementation(APlayerCharacterMagicTrigger* InPlayerCharacter) override;

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



};
