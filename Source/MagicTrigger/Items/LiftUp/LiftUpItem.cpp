// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс поднимаемых и таскаемых предметов.
 */


#include "LiftUpItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavAreas/NavArea_Obstacle.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"

 // Sets default values
ALiftUpItem::ALiftUpItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());

	FHitResult HitResultTmp = FHitResult();
	Box->SetRelativeLocation(FVector(0, 0, 20), false, &HitResultTmp, ETeleportType::None);
	Box->SetBoxExtent(FVector(20, 20, 20), false);

	Box->AreaClass = UNavArea_Obstacle::StaticClass();
	Box->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Box->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Attack, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_InteractNPC, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Overlap);

	InteractCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(GetRootComponent());

	InteractCollision->SetRelativeLocation(FVector(0, 0, 20), false, &HitResultTmp, ETeleportType::None);
	InteractCollision->SetBoxExtent(FVector(20, 20, 20), false);

	InteractCollision->AreaClass = UNavArea_Obstacle::StaticClass();
	InteractCollision->SetCollisionObjectType(ECollisionChannel::ECC_InteractNPC);
	InteractCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractCollision->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Overlap);

	AttachSocket = FName(TEXT("None"));
}

// Called when the game starts or when spawned
void ALiftUpItem::BeginPlay()
{
	Super::BeginPlay();

}


void ALiftUpItem::SetSimulatePhysics(bool bSimulate)
{
	StaticMesh->SetSimulatePhysics(bSimulate);
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	Box->AttachToComponent(GetRootComponent(), AttachmentRules, NAME_None);
	InteractCollision->AttachToComponent(GetRootComponent(), AttachmentRules, NAME_None);
}

FName ALiftUpItem::GetAttachSocket_IF_Implementation() const
{
	return AttachSocket;
}

void ALiftUpItem::SetSimulatePhysics_IF_Implementation(bool bSimulate)
{
	SetSimulatePhysics(bSimulate);
}

FText ALiftUpItem::GetInteractionText_IF_Implementation() const
{
	return InteractionText;
}

void ALiftUpItem::Interact_IF_Implementation(APlayerCharacterMagicTrigger* InPlayerCharacter)
{
	if (!InPlayerCharacter)
	{
		DEBUGMESSAGE("!InPlayerCharacter");
		return;
	}
	PlayerCharacter = InPlayerCharacter;
	InPlayerCharacter->LiftUpLiftUpItem();
}

void ALiftUpItem::IsObserved_Implementation()
{
	StaticMesh->SetRenderCustomDepth(true);
}

void ALiftUpItem::IsNotObserved_Implementation()
{
	StaticMesh->SetRenderCustomDepth(false);
}


