// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Платформа для подъема перса к скале.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSelectionPlugin/Public/TargetSelectionInterface.h"
#include "Lift.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class UQuestSevenfoldSphereComponent;

UCLASS()
class MAGICTRIGGER_API ALift : public AActor,
	public ITargetSelectionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALift();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lift|Components")
		UBoxComponent* BoundsCollision;
	//Для реакции на перса.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lift|Components")
		UBoxComponent* OverlapCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lift|Components")
		UStaticMeshComponent* Mesh;
	//Для присоединения перса во время движения.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lift|Components")
		USceneComponent* AttachCharacterPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lift|Components")
		UQuestSevenfoldSphereComponent* QuestSevenfoldSphereComponent;


	/**
	 * Methods
	 */
public:

	UFUNCTION()
		void LiftBeginOverlapCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void LiftEndOverlapCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/**
	 * TargetSelectionInterface
	 */
	virtual void IsObserved_Implementation() override;
	virtual void IsNotObserved_Implementation() override;



};
