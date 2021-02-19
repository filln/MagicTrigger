// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс поднимаемых и таскаемых предметов.
 */


#include "LiftingItem.h"

// Sets default values
ALiftingItem::ALiftingItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttachSocket = FName(TEXT("None"));

}

// Called when the game starts or when spawned
void ALiftingItem::BeginPlay()
{
	Super::BeginPlay();
	
}


FName ALiftingItem::GetAttachSocket_IF_Implementation() const
{
	return this->AttachSocket;
}

