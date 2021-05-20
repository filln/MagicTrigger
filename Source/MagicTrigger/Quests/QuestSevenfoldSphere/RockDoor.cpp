// Fill out your copyright notice in the Description page of Project Settings.


#include "RockDoor.h"
#include "NavAreas\NavArea_Obstacle.h"
#include "Components\SphereComponent.h"
#include "Components\BoxComponent.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"

// Sets default values
ARockDoor::ARockDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RootCollision"));
	SetRootComponent(RootCollision);

	DoorCollision = CreateDefaultSubobject<USphereComponent>(TEXT("DoorCollision"));
	DoorCollision->SetupAttachment(GetRootComponent());
	DoorCollision->SetSphereRadius(41);
	FHitResult HitResultTmp = FHitResult();
	DoorCollision->SetRelativeLocation(FVector(-41.4, 0, -85.1), false, &HitResultTmp, ETeleportType::None);
	DoorCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	DoorCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DoorCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	DoorCollision->SetCollisionResponseToChannel(ECC_Attack, ECollisionResponse::ECR_Ignore);
	DoorCollision->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Ignore);
	DoorCollision->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Ignore);
	DoorCollision->SetCollisionResponseToChannel(ECC_InteractNPC, ECollisionResponse::ECR_Ignore);
	DoorCollision->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Ignore);

}

// Called when the game starts or when spawned
void ARockDoor::BeginPlay()
{
	Super::BeginPlay();
	this->DoorInitialLocation = this->DoorCollision->GetRelativeLocation();
}



