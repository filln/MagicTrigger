// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Для взаимодействия
квестовых акторов.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestOpenLastDoorManager.generated.h"

 //class USevenfoldSphereComponent;
class AOpenLastDoorPedestalParent;
class AInflatedSphere;
class ALastDoorLevel1;

UCLASS()
class MAGICTRIGGER_API AQuestOpenLastDoorManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestOpenLastDoorManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		FVector PointOfPedestal1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		FVector PointOfPedestal2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		FVector PointOfPedestal3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		FVector PointOfPedestal4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		FVector PointOfPedestal5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		FVector PointOfPedestal6;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		FVector PointOfPedestal7;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		FVector SpawnScalePedestals;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		FTransform SpawnTransformLastDoor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float TimersDeltaTime;
	//Продолжительность увеличения свечения последней накачанной сферы.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float EmissiveSphereTime;
	//Продолжительность поворота накачанной сферы в сторону камня двери.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float RotationSphereTime;
	//Макс. свечение накачанной сферы.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float MaxEmissiveSphere;
	//Макс. поворот накачанной сферы в сторону камня двери, по оси Y (Pitch).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float MaxRotationSphere;
	//Время движения накачанной сферы в сторону камня двери.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float MoveSphereTime;
	//Макс. скейл накачанной сферы в процессе ее движения к камню двери.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float MaxScaleSphere;
	//Время скейла-увеличения накачнной сферы в процессе ее движения к камню двери.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float ScaleSphereTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float MaxEmissiveGem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float EmissiveGemTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestOpenLastDoorManager|Settings")
		float OpenLastDoorOverTime;

	UPROPERTY()
		TArray<AOpenLastDoorPedestalParent*> PedestalsArray;
	bool bCanWork;
private:
	FTimerHandle BeginPlayTimer;
	FTimerDelegate BeginPlayDelegate;
	float BeginPlayTimerDeltaTime;
	FTimerHandle MainTimer;
	AInflatedSphere* InflatedSphere;
	ALastDoorLevel1* LastDoor;
	float EmissiveSphereDeltaValue;
	float RotationSphereDeltaValue;
	float CurrentRotationSphere;
	float CurrentEmissiveSphere;
	float CurrentScaleSphere;
	float ScaleSphereDeltaValue;
	float CurrentEmissiveGem;
	float EmissiveGemDeltaValue;

	/**
	 * Methods
	 */
public:

	void IncreaseEmissiveLastInflateSphere();
	UFUNCTION()
		void SSphereFinish();
	UFUNCTION(BlueprintCallable, Category = "QuestOpenLastDoorManager")
		void ContinueAfterRightSummaryPlacings();
private:
	void StartBeginPlayTimer();
	void SpawnActors();
	bool CheckOnRightPlacingsOnEveryPedestal();
	void ReturnPedestalsToBeginAfterWrongSummaryPlacings();
	void IncreaseEmissiveInflateSphereUpdate();
	void IncreaseRotationInflateSphere();
	void IncreaseRotationInflateSphereUpdate();
	void MoveAndScaleInflateSphere();
	void IncreaseScaleInflateSphere();
	void IncreaseScaleInflateSphereUpdate();
	void DecreaseScaleInflateSphere();
	void DecreaseScaleInflateSphereUpdate();
	void IncreaseEmissiveGem();
	void IncreaseEmissiveGemUpdate();
	void DeactivatePedestals();
	void OpenLastDoor();
};
