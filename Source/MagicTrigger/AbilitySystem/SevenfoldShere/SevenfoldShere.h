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
		UStaticMeshComponent* Mesh;

	/**
	 * Methods
	 */


	
};
