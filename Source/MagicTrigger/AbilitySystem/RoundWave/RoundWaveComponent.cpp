// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#include "RoundWaveComponent.h"
#include "MagicTrigger/AbilitySystem/AbilitySystemManager.h"
#include "MagicTrigger/Data/DebugMessage.h"


// Sets default values for this component's properties
URoundWaveComponent::URoundWaveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}


// Called when the game starts
void URoundWaveComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		DEBUGMESSAGE("!Owner");
		return;
	}
	AbilitySystemManager = Cast<AAbilitySystemManager>(Owner);
	if (!AbilitySystemManager)
	{
		DEBUGMESSAGE("!AbilitySystemManager");
		return;
	}

	
}


// Called every frame
void URoundWaveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URoundWaveComponent::Use()
{
	AbilitySystemManager->UseRoundWave();
}

