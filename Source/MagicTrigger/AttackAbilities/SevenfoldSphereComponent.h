// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * 
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SevenfoldSphereComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Category = "SevenfoldSphereComponent")
class MAGICTRIGGER_API USevenfoldSphereComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USevenfoldSphereComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * 
	 */
	UFUNCTION(BlueprintCallable, Category = "SevenfoldSphereComponent")
		void UseSevenfoldSphereAbility();

		
};
