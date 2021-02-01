// Fill out your copyright notice in the Description page of Project Settings.


#include "DemonCastle.h"

// Sets default values
ADemonCastle::ADemonCastle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADemonCastle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADemonCastle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

