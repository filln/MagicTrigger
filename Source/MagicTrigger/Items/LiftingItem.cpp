// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс поднимаемых и таскаемых предметов.
 */


#include "LiftingItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet\GameplayStatics.h"
#include "NavAreas\NavArea_Obstacle.h"

 // Sets default values
ALiftingItem::ALiftingItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

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
void ALiftingItem::BeginPlay()
{
	Super::BeginPlay();
	InteractionText = FText::FromStringTable("/Game/MagicTrigger/Data/ST_Interaction.ST_Interaction", "LiftingTip");
	if (InteractionText.IsEmpty())
	{
		DEBUGMESSAGE("InteractionText.IsEmpty()");

	}
	StartBeginPlayTimer_IF_Implementation();
}


FName ALiftingItem::GetAttachSocket_IF_Implementation() const
{
	return this->AttachSocket;
}

void ALiftingItem::SetPlayingAnimationLiftUp_IF_Implementation(bool bPlaying)
{
}

void ALiftingItem::SetPlayingAnimationPutDown_IF_Implementation(bool bPlaying)
{
}

void ALiftingItem::SetSimulatePhysics_IF_Implementation(bool bSimulate)
{
}

FText ALiftingItem::GetInteractionText_IF_Implementation() const
{
	return this->InteractionText;
}

void ALiftingItem::Interact_IF_Implementation()
{
}

void ALiftingItem::IsObserved_Implementation()
{
	this->StaticMesh->SetRenderCustomDepth(true);
}

void ALiftingItem::IsNotObserved_Implementation()
{
	this->StaticMesh->SetRenderCustomDepth(false);
}

void ALiftingItem::StartBeginPlayTimer_IF_Implementation()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}
	FTimerDelegate BeginPlayDelegate;
	BeginPlayDelegate.BindLambda
	(
		[=]
	()
	{
		if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			GetWorld()->GetTimerManager().ClearTimer(this->BeginPlayTimer);
			this->PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		}
		else
		{
			DEBUGMESSAGE("!UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)");
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(this->BeginPlayTimer, BeginPlayDelegate, 0.2, true);
}

