// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс метаемых предметов.
 */

#pragma once

#include "CoreMinimal.h"
#include "LiftingItem.h"
#include "ThrowableItem.generated.h"

class UProjectileMovementComponent;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API AThrowableItem : public ALiftingItem
{
	GENERATED_BODY()

public:
	AThrowableItem();

public:

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

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "ThrowableItem")
		UProjectileMovementComponent* ProjectileMovementComponent;

};
