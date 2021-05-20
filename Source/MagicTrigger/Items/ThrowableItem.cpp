// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс метаемых предметов.
 */


#include "ThrowableItem.h"
#include "MagicTrigger\Interfaces\AnimationManagerInterface.h"
#include "MagicTrigger\Interfaces\TrowableRockResponseInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework\ProjectileMovementComponent.h"
#include "GameFramework\Character.h"

AThrowableItem::AThrowableItem()
{
	Damage = 5;
	Speed = 1500;
	AttachSocket = FName(TEXT("ThrowableRightHand"));

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
}

void AThrowableItem::SetPlayingAnimationLiftUp_IF_Implementation(bool bPlaying)
{
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PlayerCharacter))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PlayerCharacter)");
		return;
	}
	IAnimationManagerInterface::Execute_SetPlayingAnimationLiftUp1Hand_IF(this->PlayerCharacter, bPlaying);
}

void AThrowableItem::SetPlayingAnimationPutDown_IF_Implementation(bool bPlaying)
{
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PlayerCharacter))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PlayerCharacter)");
		return;
	}
	IAnimationManagerInterface::Execute_SetPlayingAnimationPutDown1Hand_IF(this->PlayerCharacter, bPlaying);
}

void AThrowableItem::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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
