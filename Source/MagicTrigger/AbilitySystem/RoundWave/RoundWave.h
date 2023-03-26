// Copyright 2023 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/*
јктор абилки круговой волны. јктор, который спавнитс€ при применении абилки и показывает волну.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoundWave.generated.h"

class UMaterialInterface;
class UStaticMeshComponent;
class UTexture;
class USphereComponent;
class APlayerCharacterMagicTrigger;

UCLASS()
class MAGICTRIGGER_API ARoundWave : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoundWave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:
	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWave|Components")
		USphereComponent* SphereCollision;
	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWave|Components")
		UStaticMeshComponent* Mesh;

	/**
	 *»сточник дл€ создани€ динамического материала. ћатериал создаетс€ в URoundWaveComponent.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWave")
		UMaterialInterface* SourceMaterial;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoundWave|Settings")
		float Damage;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoundWave")
		APlayerCharacterMagicTrigger* PlayerCharacter;

	/**
	 * 
	 */
	FVector InitialScale;
private:
	/**
	 *
	 */


	 /**
	  * Methods
	  */
public:
	UFUNCTION()
		void OnSphereCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:



};
