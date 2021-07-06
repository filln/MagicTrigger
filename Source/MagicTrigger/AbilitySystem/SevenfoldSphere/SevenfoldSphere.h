// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Абстрактный родительский
класс для всех типов сфер.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SevenfoldSphere.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UMaterialInstanceDynamic;
class UMaterialInterface;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API ASevenfoldSphere : public AActor
{
	GENERATED_BODY()
public:
	ASevenfoldSphere();
protected:
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SevenfoldSphere|Components")
		UBoxComponent* Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SevenfoldSphere|Components")
		UStaticMeshComponent* Mesh;
	//Material
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphere|Settings")
		FName EmissiveMultiplierName;
	UPROPERTY()
		UMaterialInstanceDynamic* Material;
	UPROPERTY()
		UMaterialInterface* SourceMaterial;

	//Порядковый номер сферы (какая по счету при спавне.)
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphere|Settings")
		int32 Number;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphere|Settings")
		float MaxEmissive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphere|Settings")
		float MaxScaleMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphere|Settings")
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
