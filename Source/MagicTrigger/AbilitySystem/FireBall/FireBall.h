// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Фаербол, используется для атаки. Работает в связке с UFireBallComponent.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicTrigger\Data\AbilitySystem\FireBallMoveToTargetInputsStruct.h"
#include "FireBall.generated.h"

class UMaterialInterface;
class UStaticMeshComponent;
class UTexture;
class UParticleSystem;
class USphereComponent;

UCLASS()
class MAGICTRIGGER_API AFireBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireBall();

	/**
	 * Variables
	 */
public:
	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireBall|Components")
		USphereComponent* SphereCollision;
	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireBall|Components")
		UStaticMeshComponent* Mesh;
	/**
	 * Текстура для SourceMaterial.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireBall")
		UTexture* Texture;
	/**
	 *Источник для создания динамического материала. Материал создается в UFireBallComponent.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireBall")
		UMaterialInterface* SourceMaterial;
	/**
	 *Частицы для эффекта, когда фаербол достигает цели.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireBall")
		UParticleSystem* EmitterTemplate;
	/**
	 *Цвет сияния.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireBall")
		FLinearColor EmissiveColor;
	/**
	 * Текущий множитель масштабирования, используется в UFireBallComponent.
	 */
	float CurrentMultiplierOfScale;
	/**
	 *Текущий множитель сияния, используется в UFireBallComponent.
	 */
	float CurrentMultiplierOfEmissive;

private:
	/**
	 *
	 */
	FVector InitialScale;

	/**
	 * Methods
	 */
public:
	/**
	 *
	 */
	FVector GetInitialScale() const { return InitialScale; }
	/**
	 *
	 */
	void SaveInitialScale();
	/**
	 *
	 */
	void MoveToTarget(FFireBallMoveToTargetInputsStruct FireBallMoveToTargetInputsStruct);
	/**
	 * 
	 */
	void DoAfterMoveToTarget(FFireBallMoveToTargetInputsStruct FireBallMoveToTargetInputsStruct);
	/**
	 *
	 */
	void DoDamage(FFireBallMoveToTargetInputsStruct FireBallMoveToTargetInputsStruct);
	/**
	 *
	 */
	float CalcTimeOfMoveToTarget(AActor* Target, float Speed);

};
