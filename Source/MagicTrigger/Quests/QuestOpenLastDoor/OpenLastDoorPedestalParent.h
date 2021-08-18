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
class ASevenfoldSphere;
class AInflatedSphere;
class AQuestOpenLastDoorManager;

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
		USceneComponent* InflateSphereSpawnPoint;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float CurrentEmissive;
	//Запомнить начальную светимость.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float MaxEmissive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float TimersDeltaTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float DeltaRotationBuffFloor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float Max1DeltaRotationSpheres;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float Max2DeltaRotationSpheres;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float Max3DeltaRotationSpheres;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float RotationAndEmissiveSpheresTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float MinEmissive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float MoveSpheresTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float MoveSpheresHalfTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		float ChangeRotationSpheresTime;
		//Макс. количество накачек сферы.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		int32 MaxCountOfUpInflates;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		int32 MaxCountOfDownInflates;
		//Увеличение скейла каждую накачку, т.е. каждый вызов InflateSphere()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		FVector IncreaseScaleInflateBigDelta;
		//Начальный скейл ScaleInflateBigDelta + IncreaseScaleInflateBigDelta равен скейлу, до которого увеличивается сфера каждую накачку, т.е. каждый вызов InflateSphere()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Settings")
		FVector ScaleInflateBigDelta;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Materials")
		UMaterialInstanceDynamic* SpheresMaterial;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "OpenLastDoorPedestalParent|Materials")
		UMaterialInstanceDynamic* IndicationMaterial;

	bool bRightPlacing;
	AInflatedSphere* InflatedSphere;
	AQuestOpenLastDoorManager* QuestOpenLastDoorManager;
private:
	UPROPERTY()
		UMaterialInterface* SpheresSourceMaterial;
	UPROPERTY()
		UMaterialInterface* IndicationSourceMaterial;
	float CurrentDeltaRotationSpheres;
	float RotationSpheresDeltaValue;
	float EmissiveSpheresDeltaValue;
	float IncreaseRotationToMax2SpheresDeltaValue;
	float MovePumpDeltaZ;
	float ScaleInflateDeltaZ;
	float ScaleInflateDeltaXY;
	int32 CountOfUpInflates;
	int32 CountOfDownInflates;
	bool bCanWork;
	FTimerHandle RotationComponentsTimer;
	FTimerHandle InflateSphereTimer;
	FTimerHandle MainTimer;
	ASevenfoldSphere* SevenfoldSphere;
	FHitResult HitResultTmp;

protected:

	/**
	 * Methods
	 */
public:
	void ReturnToBeginAfterWrongSummaryPlacings();
	void IncreaseRotationSpheresToMax3();
	void Deactivate();

	//SphereCollision BeginOverlap.
	UFUNCTION()
	void Activate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	void FindAndSetStaticMesh(UStaticMeshComponent* InStaticMeshComponent, ConstructorHelpers::FObjectFinder<UStaticMesh>& InMeshObj);
	UMaterialInterface* FindAndSetMaterial(UStaticMeshComponent* InStaticMeshComponent, int32 InElementIndex, ConstructorHelpers::FObjectFinder<UMaterialInterface>& InSourceMaterialInterfaceObj);
	void SetupMaterials();
	void RotationComponentsUpdate();
	void DecreaseRotationAndEmissiveSpheresUpdate();
	void MoveSpheresToHighPoint();
	void CheckOnRightPlacingInThisPedestal();
	void ContinueAfterRightPlacing();
	void IncreaseRotationSpheresToMax2Update();
	void ReturnToBeginAfterWrongPlacing();
	void IncreaseRotationAndEmissiveSpheresUpdate();
	void DecreaseRotationFromMax2ToZeroUpdate();
	void IncreaseRotationSpheresToMax3Update();
	void SwitchOnPump();
	void MovePumpDownUpdate();
	void InflateSphere();
	void InflateSphereUpdate();
	void MovePumpUpUpdate();
	void MoveIflateSphereToPedestal7();
	void DeleteUnusedInflateSpheres();
	void DeactivateUpdate();

};
