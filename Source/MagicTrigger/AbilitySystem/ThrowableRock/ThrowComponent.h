// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Для метания предметов.
 */
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICTRIGGER_API UThrowComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UThrowComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
