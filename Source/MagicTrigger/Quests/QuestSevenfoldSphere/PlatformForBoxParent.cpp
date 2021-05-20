// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Квестовая платформа, на которую ставятся квестовые боксы.
 */


#include "PlatformForBoxParent.h"
#include "NavAreas\NavArea_Obstacle.h"
#include "Components\BoxComponent.h"
#include "Components\StaticMeshComponent.h"
#include "Kismet\KismetSystemLibrary.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Quests\QuestSevenfoldSphere\BoxForPlatformParent.h"


// Sets default values
APlatformForBoxParent::APlatformForBoxParent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	BoundsCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundsCollision"));
	SetRootComponent(BoundsCollision);
	BoundsCollision->SetBoxExtent(FVector(48, 48, 6.4), false);
	BoundsCollision->AreaClass = UNavArea_Obstacle::StaticClass();
	BoundsCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoundsCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoundsCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BoundsCollision->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	BoundsCollision->SetCollisionResponseToChannel(ECC_Attack, ECollisionResponse::ECR_Ignore);
	BoundsCollision->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Ignore);
	BoundsCollision->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Overlap);
	BoundsCollision->SetCollisionResponseToChannel(ECC_InteractNPC, ECollisionResponse::ECR_Ignore);
	BoundsCollision->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Ignore);

	PlacingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PlacingCollision"));
	PlacingCollision->SetupAttachment(GetRootComponent());
	PlacingCollision->AreaClass = UNavArea_Obstacle::StaticClass();
	PlacingCollision->SetBoxExtent(FVector(40, 40, 6.4), false);
	FHitResult HitResultTmp = FHitResult();
	PlacingCollision->SetRelativeLocation(FVector(0, 0, 13), false, &HitResultTmp, ETeleportType::None);
	PlacingCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	PlacingCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PlacingCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	PlacingCollision->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Ignore);
	PlacingCollision->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	PlacingCollision->SetCollisionResponseToChannel(ECC_Attack, ECollisionResponse::ECR_Ignore);
	PlacingCollision->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Ignore);
	PlacingCollision->OnComponentBeginOverlap.AddDynamic(this, &APlatformForBoxParent::MoveDown);
	PlacingCollision->OnComponentEndOverlap.AddDynamic(this, &APlatformForBoxParent::MoveUp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionProfileName(FName(TEXT("BlockAllDynamic")), false);
	Mesh->SetRelativeScale3D(FVector(0.96, 0.96, 0.13));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/SM_1M_Cube"));
	if (MeshObj.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()");
	}

}

void APlatformForBoxParent::BeginPlay()
{
	Super::BeginPlay();

	this->InitialLocation = GetActorLocation();

}

void APlatformForBoxParent::MoveUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABoxForPlatformParent* CurrentPlacingBox = Cast<ABoxForPlatformParent>(OtherActor);
	if (!CurrentPlacingBox)
	{
		return;
	}
	if (CurrentPlacingBox->Box != OtherComp)
	{
		return;
	}
	if (this->CurrentBox != CurrentPlacingBox)
	{
		return;
	}
	this->CurrentBox = nullptr;

	//Delay 1 sec. т.к. когда бокс начинает подниматься, уже происходит енд оверлап, а анимация еще не подняла бокс.
	FTimerHandle TmpTimer;
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		Move(this->InitialLocation.Z);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(TmpTimer, TmpDelegate, 1, false);

}

void APlatformForBoxParent::MoveDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (this->CurrentBox)
	{
		return;
	}
	ABoxForPlatformParent* CurrentPlacingBox = Cast<ABoxForPlatformParent>(OtherActor);
	if (!CurrentPlacingBox)
	{
		return;
	}
	if (CurrentPlacingBox->Box != OtherComp)
	{
		return;
	}

	this->CurrentBox = CurrentPlacingBox;

	float ExtentZ = 2 * this->Mesh->Bounds.BoxExtent.Z;
	float TargetLocationZ = this->InitialLocation.Z - ExtentZ;
	Move(TargetLocationZ);

}

void APlatformForBoxParent::Move(float InTargetRelativeLocationZ)
{
	FVector TargetRelativeLocation = FVector(this->InitialLocation.X, this->InitialLocation.Y, InTargetRelativeLocationZ);
	FRotator TargetRelativeRotation = GetActorRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		1,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void APlatformForBoxParent::IsObserved_Implementation()
{
	this->Mesh->SetRenderCustomDepth(true);
}

void APlatformForBoxParent::IsNotObserved_Implementation()
{
	this->Mesh->SetRenderCustomDepth(false);
}
