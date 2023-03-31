// Copyright 2023 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "RoundWave.h"
#include "MagicTrigger/Data/CollisionChannelsMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MagicTrigger/Enemy/EnemyCharacterMagicTrigger.h"

// Sets default values
ARoundWave::ARoundWave()
{
	Damage = 1.0;
	ApplyDamageDelay = 1.8;
	ImpulseForceX = 1300;
	ImpulseForceY = 1300;
	ImpulseForceZ = 700;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	//SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	//SetRootComponent(SphereCollision);
	//SphereCollision->SetSphereRadius(500);
	//SphereCollision->SetEnableGravity(false);
	//SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//SphereCollision->SetCollisionObjectType(ECC_AttackAbility);
	//SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	BoxCollision->SetNotifyRigidBodyCollision(true);
	BoxCollision->SetBoxExtent(FVector(500, 500, 20000));
	BoxCollision->SetEnableGravity(false);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionObjectType(ECC_RoundWave);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Block);

	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ARoundWave::OnSphereCollisionBeginOverlap);
	//BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ARoundWave::OnSphereCollisionBeginOverlap);
	BoxCollision->OnComponentHit.AddDynamic(this, &ARoundWave::OnCollisionHit);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObject(TEXT("/Game/MagicTrigger/Meshes/AttackAbilities/SM_RoundWaveRadialDisk"));
	if (MeshObject.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObject.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObject.Succeeded()");
	}
	Mesh->SetEnableGravity(false);
	Mesh->SetGenerateOverlapEvents(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SourceMaterialObject(TEXT("/Game/MagicTrigger/Materials/AbilitySystem/MI_RoundWave"));
	if (SourceMaterialObject.Succeeded())
	{
		SourceMaterial = SourceMaterialObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!SourceMaterialObject.Succeeded()");
	}

}

// Called when the game starts or when spawned
void ARoundWave::BeginPlay()
{
	Super::BeginPlay();
	
}

//void ARoundWave::OnSphereCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	ACharacter* PlayerCharacterTmp = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
//	if (!PlayerCharacterTmp)
//	{
//		DEBUGMESSAGE("!PlayerCharacterTmp");
//		return;
//	}
//	PlayerCharacter = Cast<APlayerCharacterMagicTrigger>(PlayerCharacterTmp);
//	if (!PlayerCharacter)
//	{
//		DEBUGMESSAGE("!PlayerCharacter");
//		return;
//	}
//	if (!this->PlayerCharacter->GetController())
//	{
//		DEBUGMESSAGE("!this->PlayerCharacter->GetController()");
//		return;
//	}
//	if (PlayerCharacter == OtherActor)
//	{
//		return;
//	}
//	DoForce(OtherActor);
//}

void ARoundWave::OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
	if (PlayerCharacter == OtherActor)
	{
		return;
	}
	DoForce(OtherActor);
}

void ARoundWave::DoForce(AActor* EnemyActor)
{
	FVector Impulse = EnemyActor->GetActorLocation() - PlayerCharacter->GetActorLocation();
	Impulse.Normalize();
	Impulse.X *= ImpulseForceX;
	Impulse.Y *= ImpulseForceY;
	Impulse.Z += ImpulseForceZ;

	ACharacter* EnemyCharacter = Cast<ACharacter>(EnemyActor);
	if (EnemyCharacter)
	{
		EnemyCharacter->LaunchCharacter(Impulse, true, true);
		//Задержка нужна, т.к. анимация получения дамага мешает сработке LaunchCharacter.
		FTimerHandle TmpTimer;
		FTimerDelegate TmpDelegate;
		TmpDelegate.BindLambda
		(
			[=]()
			{
				UGameplayStatics::ApplyDamage(EnemyActor, this->Damage, this->PlayerCharacter->GetController(), this, nullptr);
			}
		);
		GetWorld()->GetTimerManager().SetTimer(TmpTimer, TmpDelegate, ApplyDamageDelay, false);

	}

}


