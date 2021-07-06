// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 

/**
 * Базовый абстрактный класс для всех пьедесталов для установки семикратных сфер.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OpenLastDoorPedestalParent.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API AOpenLastDoorPedestalParent : public AActor
{
	GENERATED_BODY()

public:
	AOpenLastDoorPedestalParent();

protected:

	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		USphereComponent* SphereCollision;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		USceneComponent* HighPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		USceneComponent* LowerPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		USceneComponent* SpheresCentralPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Ruins_Player_Pedestal_Inner;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Ruins_GreenBuffFloor;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Ruins_Buff_Floor_Lower;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* JungleTrim_Metal_Whole;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* JungleTrim_Metal_Whole_Little;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Sphere1;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Sphere2;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Sphere3;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Sphere4;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Sphere5;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Sphere6;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Components")
		UStaticMeshComponent* Sphere7;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float HighPointZLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float LowerPointZLocation;
	//Общая светимость на 1 сферу.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float TotalEmissive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float IndicationEmissive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		FName EmissiveMultiplierName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		FName EmissivePowerName;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		int32 CountOfSpheres;
	//Светимость, поделенная на количество сфер.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OpenLastDoorPedestalParent|Settings")
		float CurrentEmissive;
	//Запомнить начальную светимость.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OpenLastDoorPedestalParent|Settings")
		float MaxEmissive;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Materials")
		UMaterialInstanceDynamic* SpheresMaterial;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Materials")
		UMaterialInstanceDynamic* IndicationMaterial;
private:
	UPROPERTY()
		UMaterialInterface* SpheresSourceMaterial;
	UPROPERTY()
		UMaterialInterface* IndicationSourceMaterial;

protected:

	/**
	 * Methods
	 */
private:
	void FindAndSetStaticMesh(UStaticMeshComponent* InStaticMeshComponent, ConstructorHelpers::FObjectFinder<UStaticMesh>& InMeshObj);
	UMaterialInterface* FindAndSetMaterial(UStaticMeshComponent* InStaticMeshComponent, int32 InElementIndex, ConstructorHelpers::FObjectFinder<UMaterialInterface>& InSourceMaterialInterfaceObj);
	void SetupMaterials();

};
