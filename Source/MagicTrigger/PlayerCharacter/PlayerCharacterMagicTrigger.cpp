// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Персонаж игры.
 */


#include "PlayerCharacterMagicTrigger.h"

// Sets default values
APlayerCharacterMagicTrigger::APlayerCharacterMagicTrigger()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacterMagicTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacterMagicTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacterMagicTrigger::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/**
* AnimationManagerInterface methods.
*/
/**
 * Getters
 */
UActorComponent* APlayerCharacterMagicTrigger::GetAnimationManagerComponent_IF_Implementation() const
{
	UActorComponent* ActorComponent = nullptr;
	return ActorComponent;
}

