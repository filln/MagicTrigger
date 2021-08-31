// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс метаемых предметов.
 */


#include "ThrowableItem.h"
#include "MagicTrigger/Interfaces/AnimationManagerInterface.h"
#include "MagicTrigger/Interfaces/TrowableRockResponseInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"

AThrowableItem::AThrowableItem()
{
	Damage = 5;
	Speed = 1600;
	ArcParam = 0.5;
	ArcAlpha = 0.35;

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

	FHitResult HitResultTmp = FHitResult();
	Box->SetRelativeLocation(FVector(0, 0, 30), false, &HitResultTmp, ETeleportType::None);
	Box->SetBoxExtent(FVector(30), false);
	Box->SetCollisionObjectType(ECollisionChannel::ECC_ThrowableObject);
	Box->SetCollisionResponseToChannel(ECC_ThrowableObject, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Overlap);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AThrowableItem::OnBoxBeginOverlap);

	InteractCollision->SetRelativeLocation(FVector(0, 0, 30), false, &HitResultTmp, ETeleportType::None);
	InteractCollision->SetBoxExtent(FVector(30), false);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->bBounceAngleAffectsFriction = true;
	ProjectileMovementComponent->Bounciness = 0.3;//0.2...0.6
	ProjectileMovementComponent->Friction = 0.8;//0.3...0.8

}

void AThrowableItem::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacterTmp = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacterTmp)
	{
		DEBUGMESSAGE("!PlayerCharacterTmp");
		return;
	}
	PlayerCharacter = Cast<APlayerCharacterMagicTrigger>(PlayerCharacterTmp);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	if (!this->PlayerCharacter->GetController())
	{
		DEBUGMESSAGE("!this->PlayerCharacter->GetController()");
		return;
	}
	if (!IsInterfaceImplementedBy<ITrowableRockResponseInterface>(OtherActor))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<ITrowableRockResponseInterface>(OtherActor)");
		return;
	}
	UGameplayStatics::ApplyDamage(OtherActor, this->Damage, this->PlayerCharacter->GetController(), this, nullptr);

	ITrowableRockResponseInterface::Execute_Stunning_IF(OtherActor);
}

void AThrowableItem::PrepareBeforeFly(FVector InVelocity)
{
	ProjectileMovementComponent->ProjectileGravityScale = 1;
	ProjectileMovementComponent->Bounciness = FMath::RandRange(0.2f, 0.6f);
	ProjectileMovementComponent->Friction = FMath::RandRange(0.3f, 0.8f);
	ProjectileMovementComponent->Velocity = InVelocity;

}

void AThrowableItem::PickUpItself_IF_Implementation()
{
	PlayerCharacter->PickUpThrowableItem();
}
