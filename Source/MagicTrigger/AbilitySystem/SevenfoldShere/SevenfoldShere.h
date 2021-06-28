// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Абстрактный родительский
класс для всех типов сфер.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SevenfoldShere.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UMaterialInstanceDynamic;
class UMaterialInterface;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API ASevenfoldShere : public AActor
{
	GENERATED_BODY()
public:
	ASevenfoldShere();
protected:
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SevenfoldShere|Components")
		UBoxComponent* Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SevenfoldShere|Components")
		UStaticMeshComponent* Mesh;

	//Material
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldShere|Settings")
		FName EmissiveMultiplierName;
	UPROPERTY()
		UMaterialInstanceDynamic* Material;
	UPROPERTY()
		UMaterialInterface* SourceMaterial;

	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldShere|Settings")
		float MaxEmissive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldShere|Settings")
		float MaxScaleMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldShere|Settings")
		float ScaleAndEmissiveTime;

	FVector InitialScale;

private:
	FTimerHandle IncreaseScaleAndEmissiveAfterSpawnTimer;
	FTimerHandle DecreaseScaleAndEmissiveAfterSpawnTimer;
	float DeltaEmissive;
	float DeltaScaleMultiplier;
	float CurrentEmissive;
	float CurrentScaleMultiplier;

	float TimersDeltaTime;


	/**
	 * Methods
	 */
	void IncreaseScaleAndEmissiveAfterSpawn();
	void DecreaseScaleAndEmissiveAfterSpawn();

};
