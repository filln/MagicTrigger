// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс метаемых предметов.
 */


#include "ThrowableItem.h"
#include "MagicTrigger\Interfaces\AnimationManagerInterface.h"
#include "MagicTrigger\Interfaces\TrowableRockResponseInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework\ProjectileMovementComponent.h"
#include "MagicTrigger\PlayerCharacter\PlayerCharacterMagicTrigger.h"
#include "NavAreas\NavArea_Obstacle.h"

AThrowableItem::AThrowableItem()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	Damage = 5;
	Speed = 1500;
	AttachSocket = FName(TEXT("ThrowableRightHand"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetRelativeScale3D(FVector(0.3));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/Environment/Rocks/SM_ThrowableRock"));
	if (MeshObj.Succeeded())
	{
		StaticMesh->SetStaticMesh(MeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()")
	}

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());
	FHitResult HitResultTmp = FHitResult();
	Box->SetRelativeLocation(FVector(0, 0, 30), false, &HitResultTmp, ETeleportType::None);
	Box->SetBoxExtent(FVector(30), false);
	Box->AreaClass = UNavArea_Obstacle::StaticClass();
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Box->SetCollisionObjectType(ECollisionChannel::ECC_ThrowableObject);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Box->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Attack, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_InteractNPC, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECC_ThrowableObject, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Overlap);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AThrowableItem::OnBoxBeginOverlap);

	InteractCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(GetRootComponent());
	InteractCollision->SetRelativeLocation(FVector(0, 0, 30), false, &HitResultTmp, ETeleportType::None);
	InteractCollision->SetBoxExtent(FVector(30), false);
	InteractCollision->AreaClass = UNavArea_Obstacle::StaticClass();
	InteractCollision->SetCollisionObjectType(ECollisionChannel::ECC_InteractNPC);
	InteractCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractCollision->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Overlap);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}


FText AThrowableItem::GetInteractionText_IF_Implementation() const
{
	return InteractionText;
}

void AThrowableItem::Interact_IF_Implementation(APlayerCharacterMagicTrigger* InPlayerCharacter)
{
	if (!InPlayerCharacter)
	{
		DEBUGMESSAGE("!InPlayerCharacter");
		return;
	}
	InPlayerCharacter->SetPlayingAnimationLiftUp1Hand_IF_Implementation(true);
}

void AThrowableItem::IsObserved_Implementation()
{
	StaticMesh->SetRenderCustomDepth(true);
}

void AThrowableItem::IsNotObserved_Implementation()
{
	StaticMesh->SetRenderCustomDepth(false);
}

void AThrowableItem::BeginPlay()
{
	InteractionText = FText::FromStringTable("/Game/MagicTrigger/Data/ST_Interaction.ST_Interaction", "LiftingTip");
	if (InteractionText.IsEmpty())
	{
		DEBUGMESSAGE("InteractionText.IsEmpty()");

	}
}

void AThrowableItem::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	if (!PlayerCharacter->GetController())
	{
		DEBUGMESSAGE("!PlayerCharacter->GetController()");
		return;
	}
	if (!IsInterfaceImplementedBy<ITrowableRockResponseInterface>(OtherActor))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<ITrowableRockResponseInterface>(OtherActor)");
		return;
	}
	UGameplayStatics::ApplyDamage(OtherActor, Damage, PlayerCharacter->GetController(), this, nullptr);

	ITrowableRockResponseInterface::Execute_Stunning_IF(OtherActor);
}
