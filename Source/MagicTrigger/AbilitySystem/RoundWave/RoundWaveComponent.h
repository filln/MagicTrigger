// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
	Абилка "волна" вокруг перса
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RoundWaveComponent.generated.h"

class AAbilitySystemManager;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAGICTRIGGER_API URoundWaveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URoundWaveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Variables
	 */
private:
	AAbilitySystemManager* AbilitySystemManager;

	/**
	 * Methods
	 */
public:
	void Use();


};
