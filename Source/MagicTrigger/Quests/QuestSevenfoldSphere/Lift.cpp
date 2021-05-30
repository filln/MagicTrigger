// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Платформа для подъема перса к скале.
 */


#include "Lift.h"
#include "NavAreas\NavArea_Obstacle.h"
#include "Components\BoxComponent.h"
#include "Components\StaticMeshComponent.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Quests\QuestSevenfoldSphere\QuestSevenfoldSphereComponent.h"
#include "Kismet\GameplayStatics.h"
#include "GameFramework\Character.h"

// Sets default values
ALift::ALift()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BoundsCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundsCollision"));
	SetRootComponent(BoundsCollision);
	BoundsCollision->SetBoxExtent(FVector(96, 96, 16), false);
	BoundsCollision->AreaClass = UNavArea_Obstacle::StaticClass();
	BoundsCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	BoundsCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoundsCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BoundsCollision->SetCollisionResponseToChannel(ECC_Attack, ECollisionResponse::ECR_Ignore);
	BoundsCollision->SetCollisionResponseToChannel(ECC_ThrowableObject, ECollisionResponse::ECR_Ignore);
	BoundsCollision->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Ignore);
	BoundsCollision->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Ignore);
	BoundsCollision->SetCollisionResponseToChannel(ECC_InteractNPC, ECollisionResponse::ECR_Ignore);
	BoundsCollision->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Ignore);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetRelativeScale3D(FVector(1.89, 1.89, 0.315));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/SM_1M_Cube"));
	if (MeshObj.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()");
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/Game/MagicTrigger/Materials/M_Wood_Pine"));
	if (MaterialObj.Succeeded())
	{
		Mesh->SetMaterial(0, MaterialObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MaterialObj.Succeeded()");
	}

	OverlapCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCollision"));
	OverlapCollision->SetupAttachment(GetRootComponent());
	OverlapCollision->SetBoxExtent(FVector(92, 92, 8), false);
	FHitResult HitResultTmp = FHitResult();
	OverlapCollision->SetRelativeLocation(FVector(0, 0, 24), false, &HitResultTmp, ETeleportType::None);
	OverlapCollision->AreaClass = UNavArea_Obstacle::StaticClass();
	OverlapCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	OverlapCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapCollision->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapCollision->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Overlap);
	OverlapCollision->OnComponentBeginOverlap.AddDynamic(this, &ALift::LiftBeginOverlapCharacter);
	OverlapCollision->OnComponentEndOverlap.AddDynamic(this, &ALift::LiftEndOverlapCharacter);

	AttachCharacterPoint = CreateDefaultSubobject<USceneComponent>(TEXT("AttachCharacterPoint"));
	AttachCharacterPoint->SetupAttachment(GetRootComponent());
	AttachCharacterPoint->SetRelativeLocation(FVector(0, 0, 105), false, &HitResultTmp, ETeleportType::None);
	AttachCharacterPoint->SetHiddenInGame(true);

	QuestSevenfoldSphereComponent = CreateDefaultSubobject<UQuestSevenfoldSphereComponent>(TEXT("QuestSevenfoldSphereComponent"));
}

// Called when the game starts or when spawned
void ALift::BeginPlay()
{
	Super::BeginPlay();

	QuestSevenfoldSphereComponent->InitialLocation = GetActorLocation();
	QuestSevenfoldSphereComponent->AttachCharacterPoint = AttachCharacterPoint;
	QuestSevenfoldSphereComponent->Mesh = Mesh;
	QuestSevenfoldSphereComponent->OverlapCollision = OverlapCollision;

}

void ALift::LiftBeginOverlapCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (!Character || !OtherCharacter)
	{
		return;
	}
	if (Character != OtherCharacter)
	{
		return;
	}

	QuestSevenfoldSphereComponent->LiftBeginOverlapCharacter(OtherComp);
}

void ALift::LiftEndOverlapCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (!Character || !OtherCharacter)
	{
		return;
	}
	if (Character != OtherCharacter)
	{
		return;
	}

	QuestSevenfoldSphereComponent->LiftEndOverlapCharacter(OtherComp);
}

void ALift::IsObserved_Implementation()
{
	Mesh->SetRenderCustomDepth(true);
}

void ALift::IsNotObserved_Implementation()
{
	Mesh->SetRenderCustomDepth(false);
}



