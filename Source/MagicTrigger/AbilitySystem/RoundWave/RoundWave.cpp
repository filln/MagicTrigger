// Copyright 2023 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "RoundWave.h"
#include "MagicTrigger/Data/CollisionChannelsMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARoundWave::ARoundWave()
{
	Damage = 1.0;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(500);
	SphereCollision->SetEnableGravity(false);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECC_AttackAbility);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Overlap);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ARoundWave::OnSphereCollisionBeginOverlap);

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
	//Mesh->SetMobility(EComponentMobility::Static);

	//static ConstructorHelpers::FObjectFinder<UTexture> TextureObject(TEXT("/Game/MagicTrigger/Textures/T_FireBall_D"));
	//if (TextureObject.Succeeded())
	//{
	//	Texture = TextureObject.Object;
	//}
	//else
	//{
	//	DEBUGMESSAGE("!TextureObject.Succeeded()");
	//}
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

void ARoundWave::OnSphereCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

	UGameplayStatics::ApplyDamage(OtherActor, this->Damage, this->PlayerCharacter->GetController(), this, nullptr);
}



