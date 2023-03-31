// Copyright 2023 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/*
Актор абилки круговой волны. Актор, который спавнится при применении абилки и показывает волну.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoundWave.generated.h"

class UMaterialInterface;
class UStaticMeshComponent;
class UTexture;
//class USphereComponent;
class UBoxComponent;
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
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWave|Components")
	//	USphereComponent* SphereCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWave|Components")
		UBoxComponent* BoxCollision;
	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWave|Components")
		UStaticMeshComponent* Mesh;

	/**
	 *Источник для создания динамического материала. Материал создается в URoundWaveComponent.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWave")
		UMaterialInterface* SourceMaterial;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoundWave|Settings")
		float Damage;
	/**
	 * Задержка нужна, т.к. анимация получения дамага мешает сработке LaunchCharacter.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoundWave|Settings")
		float ApplyDamageDelay;
	/**
	 * Множители вектора для LaunchCharacter
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoundWave|Settings")
		float ImpulseForceX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoundWave|Settings")
		float ImpulseForceY;
	/**
	 * Слагаемое вектора для LaunchCharacter
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoundWave|Settings")
		float ImpulseForceZ;
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
	//UFUNCTION()
	//	void OnSphereCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
private:
	/**
	 * Отбросить всех врагов, которых коснулась волна.
	 */
	void DoForce(AActor* EnemyActor);


};
