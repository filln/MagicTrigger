// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "LastDoorLevel1.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "Components\StaticMeshComponent.h"
#include "Materials\MaterialInterface.h"


// Sets default values
ALastDoorLevel1::ALastDoorLevel1()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	EmissiveColorMultiName = FName(TEXT("EmissiveColorMulti"));

	/**
	 * Setup Components
	 */
	{
		SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
		SetRootComponent(SceneRoot);
		FHitResult HitResultTmp = FHitResult();

		//Frame
		Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
		Frame->SetupAttachment(GetRootComponent());
		Frame->SetRelativeLocation(FVector(-200, 0, 0), false, &HitResultTmp, ETeleportType::None);
		Frame->SetRelativeScale3D(FVector(1, 1.5, 1));
		Frame->SetCollisionProfileName(FName(TEXT("BlockAllDynamic")), false);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> FrameMeshObj(TEXT("/Game/MagicTrigger/Meshes/Wall_Door_400x400.Wall_Door_400x400"));
		FindAndSetStaticMesh(Frame, FrameMeshObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> FrameSourceMaterialObj(TEXT("/Game/MagicTrigger/Materials/Environment/Rocks/MI_boulder_b2"));
		FindAndSetMaterial(Frame, 0, FrameSourceMaterialObj);

		//Door
		Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
		Door->SetupAttachment(GetRootComponent());
		Door->SetRelativeLocation(FVector(0, 0, 104.16), false, &HitResultTmp, ETeleportType::None);
		Door->SetRelativeScale3D(FVector(1.3, 0.2, 2.2));
		Door->SetCollisionProfileName(FName(TEXT("BlockAllDynamic")), false);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMeshObj(TEXT("/Game/MagicTrigger/Meshes/SM_Cube.SM_Cube"));
		FindAndSetStaticMesh(Door, DoorMeshObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> DoorSourceMaterialObj(TEXT("/Game/MagicTrigger/Materials/Environment/Architecture/Castle/M_Plate_Floor_2"));
		FindAndSetMaterial(Door, 0, DoorSourceMaterialObj);

		//Gem
		Gem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gem"));
		Gem->SetupAttachment(GetRootComponent());
		Gem->SetRelativeLocation(FVector(0, 10.16, 241.91), false, &HitResultTmp, ETeleportType::None);
		Gem->SetRelativeRotation(FRotator(90, -90, 0), false, &HitResultTmp, ETeleportType::None);
		Gem->SetRelativeScale3D(FVector(2.91));
		Gem->SetCollisionProfileName(FName(TEXT("BlockAllDynamic")), false);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> GemMeshObj(TEXT("/Game/MagicTrigger/Meshes/Quests/QuestOpenLastDoor/SM_Gem.SM_Gem"));
		FindAndSetStaticMesh(Gem, GemMeshObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> GemSourceMaterialObj(TEXT("/Game/MagicTrigger/Materials/Quests/QuestOpenLastDoor/MI_Gem_OpenLastDoor"));
		GemSourceMaterial = FindAndSetMaterial(Gem, 0, GemSourceMaterialObj);

		//DoorOpenPoint
		DoorOpenPoint = CreateDefaultSubobject<USceneComponent>(TEXT("DoorOpenPoint"));
		DoorOpenPoint->SetupAttachment(GetRootComponent());
		DoorOpenPoint->SetRelativeLocation(FVector(127.08, 0, 104.16), false, &HitResultTmp, ETeleportType::None);
		DoorOpenPoint->SetRelativeRotation(Door->GetRelativeRotation(), false, &HitResultTmp, ETeleportType::None);
		DoorOpenPoint->SetRelativeScale3D(Door->GetRelativeScale3D());

		//DoorClosePoint
		DoorClosePoint = CreateDefaultSubobject<USceneComponent>(TEXT("DoorClosePoint"));
		DoorClosePoint->SetupAttachment(GetRootComponent());
		DoorClosePoint->SetRelativeLocation(Door->GetRelativeLocation(), false, &HitResultTmp, ETeleportType::None);
		DoorClosePoint->SetRelativeRotation(Door->GetRelativeRotation(), false, &HitResultTmp, ETeleportType::None);
		DoorClosePoint->SetRelativeScale3D(Door->GetRelativeScale3D());
	}

}

// Called when the game starts or when spawned
void ALastDoorLevel1::BeginPlay()
{
	Super::BeginPlay();

	GemMaterial = Gem->CreateAndSetMaterialInstanceDynamicFromMaterial(0, GemSourceMaterial);
	//Gem->SetMaterial(0, GemMaterial);
}

void ALastDoorLevel1::FindAndSetStaticMesh(UStaticMeshComponent* InStaticMeshComponent, ConstructorHelpers::FObjectFinder<UStaticMesh>& InMeshObj)
{
	if (InMeshObj.Succeeded())
	{
		InStaticMeshComponent->SetStaticMesh(InMeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!InMeshObj.Succeeded()");
	}
}

UMaterialInterface* ALastDoorLevel1::FindAndSetMaterial(UStaticMeshComponent* InStaticMeshComponent, int32 InElementIndex, ConstructorHelpers::FObjectFinder<UMaterialInterface>& InSourceMaterialInterfaceObj)
{
	UMaterialInterface* OutMaterialInterface;
	if (InSourceMaterialInterfaceObj.Succeeded())
	{
		OutMaterialInterface = InSourceMaterialInterfaceObj.Object;
		InStaticMeshComponent->SetMaterial(InElementIndex, OutMaterialInterface);

	}
	else
	{
		DEBUGMESSAGE("!InSourceMaterialInterfaceObj.Succeeded()");
		return nullptr;
	}
	return OutMaterialInterface;
}

