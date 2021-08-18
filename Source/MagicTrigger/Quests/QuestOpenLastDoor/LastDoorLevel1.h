// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * ѕќследн€€ на уровне 1 дверь, открываетс€ с помощью семикратной сферы и пьедесталов.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LastDoorLevel1.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class USceneComponent;

UCLASS()
class MAGICTRIGGER_API ALastDoorLevel1 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALastDoorLevel1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ALastDoorLevel1|Components")
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALastDoorLevel1|Components")
		UStaticMeshComponent* Frame;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALastDoorLevel1|Components")
		UStaticMeshComponent* Door;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALastDoorLevel1|Components")
		UStaticMeshComponent* Gem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ALastDoorLevel1|Components")
		USceneComponent* DoorOpenPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ALastDoorLevel1|Components")
		USceneComponent* DoorClosePoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ALastDoorLevel1|Materials")
		UMaterialInstanceDynamic* GemMaterial;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ALastDoorLevel1|Settings")
		FName EmissiveColorMultiName;

private:
	UMaterialInterface* GemSourceMaterial;
	/**
	 * Methods
	 */
public:

private:
	void FindAndSetStaticMesh(UStaticMeshComponent* InStaticMeshComponent, ConstructorHelpers::FObjectFinder<UStaticMesh>& InMeshObj);
	UMaterialInterface* FindAndSetMaterial(UStaticMeshComponent* InStaticMeshComponent, int32 InElementIndex, ConstructorHelpers::FObjectFinder<UMaterialInterface>& InSourceMaterialInterfaceObj);


};
