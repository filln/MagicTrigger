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
	 * ��������� ������ �����, ������������ �� ALift.
	 */
	FVector InitialLocation;
	USceneComponent* AttachCharacterPoint;
	UBoxComponent* OverlapCollision;
	UStaticMeshComponent* Mesh;

	/**
	 * ����������� �������� � �����
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

	//������� ��������� �����, �� �������� �� ����� ��������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		FVector UpLocation;
	//����� ����� ��� ��� ���� ������� ���� ��� �������� ����� � ��������� �� ������������ ����������� ������ �� ����������. 
	//�����, ����� ���� �� ������ ����� �� �������, � ���� ����� ����� ��������� � �����.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float PauseBeforeCheckKey;
	//���, ������� ������ ���� � ������, ������� ��������� �����-�����.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		FName OpenBigWallTag;
	//����� ��������� ����� ��� �������� �����.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float BeginOverlapMoveDownOverTime;
	//����� ������� ����� ���������, ����� ���� ������ � �����.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float EndOverlapMoveUpOverTime;
	//����� ����������� ����� � ����� ����� ����� ������� � ��������.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuestSevenfoldSphereComponent|Settings")
		float MoveCharacterToCenterLiftOverTime;
	//����� �������� ����� ����� � ����.
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
	//������������ ������������ ������ ��� ������� ������ �����.
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
	//�������� ���� ���� ��� �������� �����.
	void BeginOverlapMoveDown();
	//��������� ���� ���������, ����� ���� ������ � �����. 
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
