// Fill out your copyright notice in the Description page of Project Settings.


#include "RockDoor.h"

// Sets default values
ARockDoor::ARockDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARockDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARockDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

