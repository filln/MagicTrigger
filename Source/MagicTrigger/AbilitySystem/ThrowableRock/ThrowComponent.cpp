// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ThrowComponent.h"

// Sets default values for this component's properties
UThrowComponent::UThrowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}


// Called when the game starts
void UThrowComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



