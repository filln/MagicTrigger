// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * ����� ������ QuestSevenfoldSphere � ������-������. �����������, ���� �� 2 ��������� PlatformForBox4 � PlatformForBox5 ����� ���������� �����.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RockDoor.generated.h"

class USphereComponent;
class UBoxComponent;

UCLASS()
class MAGICTRIGGER_API ARockDoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARockDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RockDoor")
		USphereComponent* DoorCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RockDoor")
		UBoxComponent* RootCollision;
	FVector DoorInitialLocation;

};
