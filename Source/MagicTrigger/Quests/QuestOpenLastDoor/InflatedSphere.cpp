// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "InflatedSphere.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "Components\StaticMeshComponent.h"
#include "Materials\MaterialInterface.h"

// Sets default values
AInflatedSphere::AInflatedSphere()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	EmissiveMultiplierName = FName(TEXT("EmissiveMultiplier"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetRelativeScale3D(FVector(1, 1, 2));
	Mesh->SetCollisionProfileName(FName(TEXT("NoCollision")), false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/Items/SM_Sphere320.SM_Sphere320"));
	if (MeshObj.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()");
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SourceMaterialObj(TEXT("/Game/MagicTrigger/Materials/Quests/QuestOpenLastDoor/MI_InflateSphere"));
	if (SourceMaterialObj.Succeeded())
	{
		SourceMaterial = SourceMaterialObj.Object;
		Mesh->SetMaterial(0, SourceMaterial);

	}
	else
	{
		DEBUGMESSAGE("!SourceMaterialObj.Succeeded()");
	}
}

// Called when the game starts or when spawned
void AInflatedSphere::BeginPlay()
{
	Super::BeginPlay();
	Material = Mesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, SourceMaterial);
	//Mesh->SetMaterial(0, Material);
}



