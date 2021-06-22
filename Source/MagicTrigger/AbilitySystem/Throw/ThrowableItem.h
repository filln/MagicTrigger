// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс метаемых предметов.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger\Items\LiftUp\PickUpItem.h"
#include "ThrowableItem.generated.h"

class UProjectileMovementComponent;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API AThrowableItem : public APickUpItem
{
	GENERATED_BODY()

public:
	AThrowableItem();

public:

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
	void PrepareBeforeFly(FVector InVelocity);

public:
	virtual void PickUpItself_IF_Implementation() override;

};
