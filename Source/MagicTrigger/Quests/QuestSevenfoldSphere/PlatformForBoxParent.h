// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Квестовая платформа , на которую ставятся квестовые боксы. Когда бокс ставится, то платформа плавно опускается как от тяжести бокса.
 Когда бокс поднимается, платформа возвращается.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSelectionPlugin\Public\TargetSelectionInterface.h"
#include "PlatformForBoxParent.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class ABoxForPlatformParent;

UCLASS()
class MAGICTRIGGER_API APlatformForBoxParent : public AActor, public ITargetSelectionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatformForBoxParent();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatformForBoxParent|Components")
		UBoxComponent* BoundsCollision;
	/**
	 * Для реакции на квестовый бокс.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatformForBoxParent|Components")
		UBoxComponent* PlacingCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatformForBoxParent|Components")
		UStaticMeshComponent* Mesh;

	/**
	 * Бокс, который сейчас на платформе.
	 */
	ABoxForPlatformParent* CurrentBox;

private:
	FVector InitialLocation;

	/**
	 * Methods
	 */
public:

	UFUNCTION()
		void MoveUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		virtual void MoveDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	void Move(float InTargetRelativeLocationZ);

public:
	/**
	 * TargetSelectionInterface
	 */
	virtual void IsObserved_Implementation() override;
	virtual void IsNotObserved_Implementation() override;


};
