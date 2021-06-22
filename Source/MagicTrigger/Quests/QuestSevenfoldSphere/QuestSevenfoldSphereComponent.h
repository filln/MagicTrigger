// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSevenfoldSphereComponent.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class APlatformForBoxParent;
class APlatformForBox4;
class APlatformForBox5;
class ARockDoor;
class APlayerCharacterMagicTrigger;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAGICTRIGGER_API UQuestSevenfoldSphereComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UQuestSevenfoldSphereComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:
	/**
	 * Начальное данные лифта, определяются из ALift.
	 */
	FVector InitialLocation;
	USceneComponent* AttachCharacterPoint;
	UBoxComponent* OverlapCollision;
	UStaticMeshComponent* Mesh;

	/**
	 * Заполняется пипеткой в сцене
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		TArray<APlatformForBoxParent*> PlatformsForBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		TArray<APlatformForBoxParent*> PlatformsForBoxUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		TArray<APlatformForBoxParent*> PlatformsForBoxDown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		ARockDoor* RockDoor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		APlatformForBox4* PlatformForBox4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		APlatformForBox5* PlatformForBox5;

	//Верхнее положение лифта, до которого он будет долетать.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		FVector UpLocation;
	//Пауза между тем как лифт проедет вниз под тяжестью перса и проверкой на правильность расстановки боксов по платформам. 
	//Нужно, чтобы лифт не уезжал сразу жу обратно, а дать время персу спрыгнуть с лифта.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float PauseBeforeCheckKey;
	//Тег, который должен быть у боксов, которые открывают дверь-скалу.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		FName OpenBigWallTag;
	//Время опускания лифта под тяжестью перса.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float BeginOverlapMoveDownOverTime;
	//Время подъема лифта пружинкой, когда перс сходит с лифта.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float EndOverlapMoveUpOverTime;
	//Время перемещения перса в центр лифта перед аттачем и поездкой.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float MoveCharacterToCenterLiftOverTime;
	//Время движения лифта вверх и вниз.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float MoveLiftOverTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float OpenRockDoorOverTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float OpenRockDoorOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float MoveCameraSpeed;

private:
	bool bLiftDown;
	//Контролирует срабатывание логики при овелапе персом лифта.
	bool bDisableOverlapCharacter;
	FVector CurrentLocation;
	APlayerCharacterMagicTrigger* PlayerCharacter;
	UPROPERTY()
		FTimerHandle MoveCameraTimer;

	/**
	 * Methods
	 */
public:

	void LiftBeginOverlapCharacter(UPrimitiveComponent* InCharacterCollision);
	void LiftEndOverlapCharacter(UPrimitiveComponent* InCharacterCollision);

private:
	//Опускает лифт ниже под тяжестью перса.
	void BeginOverlapMoveDown();
	//Поднимает лифт пружинкой, когда перс сходит с лифта. 
	void EndOverlapMoveUp();
	void CheckKey();
	bool IsRightPlacingsDown();
	bool IsRightPlacingsUp();
	void LiftIsClosed();
	void MoveCharacterToCenterLift();
	void MoveLift(bool bMoveUp);
	void SetCharacterParameters(bool bCharacterInLift);

	UFUNCTION()
		void Platform4Or5BeginOverlapBox();
	bool IsRightPlacingsForRockDoor();
public:
	UFUNCTION(BlueprintCallable, Category = "QuestSevenfoldSphereComponent")
		void OpenRockDoor();
	UFUNCTION(BlueprintCallable, Category = "QuestSevenfoldSphereComponent")
		void LiftIsOpen();
};
