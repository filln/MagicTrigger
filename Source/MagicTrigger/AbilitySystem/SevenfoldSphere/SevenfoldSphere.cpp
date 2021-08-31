// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Абстрактный родительский
класс для всех типов сфер.
 */


#include "SevenfoldSphere.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MagicTrigger/Data/CollisionChannelsMagicTrigger.h"
#include "Materials/MaterialInterface.h"
#include "MagicTrigger/Data/DebugMessage.h"


ASevenfoldSphere::ASevenfoldSphere()
{
	EmissiveMultiplierName = FName(TEXT("EmissiveMultiplier"));
	MaxEmissive = 10;
	MaxScaleMultiplier = 2;
	CurrentEmissive = 0;
	CurrentScaleMultiplier = 1;
	ScaleAndEmissiveTime = 0.2;
	TimersDeltaTime = 0.017;
	Number = 0;

	/**
	 * Box Collision
	 */
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetBoxExtent(FVector(6), false);
	Box->SetWorldScale3D(FVector(1.5));
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionObjectType(ECC_AttackAbility);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Overlap);

	/**
	 * Mesh
	 */
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/AttackAbilities/SM_AttackAbilitySphere"));
	if (MeshObj.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObj.Object);

	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()");
	}

	/**
	 * Material
	 */
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SourceMaterialInterfaceObj(TEXT("/Game/MagicTrigger/Materials/AbilitySystem/M_AttackAbility"));
	if (SourceMaterialInterfaceObj.Succeeded())
	{
		SourceMaterial = SourceMaterialInterfaceObj.Object;
		Mesh->SetMaterial(0, SourceMaterial);

	}
	else
	{
		DEBUGMESSAGE("!SourceMaterialInterfaceObj.Succeeded()");
	}


}

void ASevenfoldSphere::BeginPlay()
{
	Super::BeginPlay();

	DeltaEmissive = MaxEmissive / (ScaleAndEmissiveTime / TimersDeltaTime);
	DeltaScaleMultiplier = MaxScaleMultiplier / (ScaleAndEmissiveTime / TimersDeltaTime);
	Material = Mesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, SourceMaterial);
	InitialScale = GetActorScale3D();
	IncreaseScaleAndEmissiveAfterSpawn();
}

void ASevenfoldSphere::IncreaseScaleAndEmissiveAfterSpawn()
{
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		if (CurrentEmissive >= MaxEmissive || CurrentScaleMultiplier >= MaxScaleMultiplier)
		{
			GetWorld()->GetTimerManager().ClearTimer(IncreaseScaleAndEmissiveAfterSpawnTimer);
			DecreaseScaleAndEmissiveAfterSpawn();
			return;
		}

		CurrentEmissive += DeltaEmissive;
		Material->SetScalarParameterValue(EmissiveMultiplierName, CurrentEmissive);

		CurrentScaleMultiplier += DeltaScaleMultiplier;
		SetActorScale3D(CurrentScaleMultiplier * InitialScale);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(IncreaseScaleAndEmissiveAfterSpawnTimer, TmpDelegate, TimersDeltaTime, true);
}

void ASevenfoldSphere::DecreaseScaleAndEmissiveAfterSpawn()
{
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		if (CurrentEmissive <= 0 || CurrentScaleMultiplier <= 1)
		{
			GetWorld()->GetTimerManager().ClearTimer(DecreaseScaleAndEmissiveAfterSpawnTimer);
			return;
		}

		CurrentEmissive -= DeltaEmissive;
		Material->SetScalarParameterValue(EmissiveMultiplierName, CurrentEmissive);

		CurrentScaleMultiplier -= DeltaScaleMultiplier;
		SetActorScale3D(CurrentScaleMultiplier * InitialScale);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(DecreaseScaleAndEmissiveAfterSpawnTimer, TmpDelegate, TimersDeltaTime, true);
}

