// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/*
Накачиваемая  пьедесталом сфера.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InflatedSphere.generated.h"

class UMaterialInstanceDynamic;
class UStaticMeshComponent;
class UMaterialInterface;

UCLASS()
class MAGICTRIGGER_API AInflatedSphere : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInflatedSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InflatedSphere")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "InflatedSphere")
		UMaterialInstanceDynamic* Material;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InflatedSphere")
		FName EmissiveMultiplierName;

private:
	UMaterialInterface* SourceMaterial;


};
