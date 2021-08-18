// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 


#include "OpenLastDoorPedestalParent.h"
#include "Components\StaticMeshComponent.h"
#include "Components\SphereComponent.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\AbilitySystem\SevenfoldSphere\SevenfoldSphere.h"
#include "MagicTrigger\Quests\QuestOpenLastDoor\InflatedSphere.h"
#include "MagicTrigger\Quests\QuestOpenLastDoor\QuestOpenLastDoorManager.h"
#include "Materials\MaterialInterface.h"
#include "Kismet\KismetSystemLibrary.h"

AOpenLastDoorPedestalParent::AOpenLastDoorPedestalParent()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	//Settings
	HighPointZLocation = 400;
	LowerPointZLocation = 72.6;
	EmissiveMultiplierName = FName(TEXT("EmissiveMultiplier"));
	EmissivePowerName = FName(TEXT("EmissivePower"));
	TotalEmissive = 50;
	CountOfSpheres = 7;
	CurrentEmissive = TotalEmissive / CountOfSpheres;
	MaxEmissive = CurrentEmissive;
	IndicationEmissive = 5;
	TimersDeltaTime = 0.017;
	DeltaRotationBuffFloor = -2;
	Max1DeltaRotationSpheres = 1;
	Max2DeltaRotationSpheres = 5;
	Max3DeltaRotationSpheres = 20;
	RotationAndEmissiveSpheresTime = 1;
	MinEmissive = 1;
	MoveSpheresTime = 1;
	MoveSpheresHalfTime = 0.5;
	ChangeRotationSpheresTime = 2;
	MaxCountOfUpInflates = 3;
	MaxCountOfDownInflates = MaxCountOfUpInflates + 1;
	bCanWork = true;
	bRightPlacing = false;
	IncreaseScaleInflateBigDelta = FVector(0.1);
	ScaleInflateBigDelta = FVector(0, 0, 0.3);


	/**
	 * Setup Components
	 */
	{
		SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
		HighPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HighPoint"));
		LowerPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LowerPoint"));
		SpheresCentralPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpheresCentralPoint"));
		InflateSphereSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("InflateSphereSpawnPoint"));
		Ruins_Player_Pedestal_Inner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ruins_Player_Pedestal_Inner"));
		Ruins_GreenBuffFloor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ruins_GreenBuffFloor"));
		Ruins_Buff_Floor_Lower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ruins_Buff_Floor_Lower"));
		JungleTrim_Metal_Whole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JungleTrim_Metal_Whole"));
		JungleTrim_Metal_Whole_Little = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JungleTrim_Metal_Whole_Little"));
		Sphere1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere1"));
		Sphere2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere2"));
		Sphere3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere3"));
		Sphere4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere4"));
		Sphere5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere5"));
		Sphere6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere6"));
		Sphere7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere7"));

		HitResultTmp = FHitResult();

		//SphereCollision
		SetRootComponent(SphereCollision);
		SphereCollision->SetSphereRadius(645, false);
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereCollision->SetCollisionObjectType(ECC_WorldStatic);
		SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		SphereCollision->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Overlap);

		//LowerPoint		
		LowerPoint->SetupAttachment(GetRootComponent());
		LowerPoint->SetRelativeLocation(FVector(0, 0, LowerPointZLocation), false, &HitResultTmp, ETeleportType::None);
		//HighPoint
		HighPoint->SetupAttachment(GetRootComponent());
		HighPoint->SetRelativeLocation(FVector(0, 0, HighPointZLocation), false, &HitResultTmp, ETeleportType::None);

		//SpheresCentralPoint
		SpheresCentralPoint->SetupAttachment(GetRootComponent());
		SpheresCentralPoint->SetRelativeLocation(FVector(0, 0, LowerPointZLocation), false, &HitResultTmp, ETeleportType::None);

		//InflateSphereSpawnPoint
		InflateSphereSpawnPoint->SetupAttachment(GetRootComponent());
		InflateSphereSpawnPoint->SetRelativeLocation(FVector(0, 0, 365), false, &HitResultTmp, ETeleportType::None);

		//Ruins_Player_Pedestal_Inner
		Ruins_Player_Pedestal_Inner->SetupAttachment(GetRootComponent());
		Ruins_Player_Pedestal_Inner->SetRelativeScale3D(FVector(1.5, 1.5, 2.5));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Ruins_Player_Pedestal_InnerMeshObj(TEXT("/Game/MagicTrigger/Meshes/Items/Pedestal/SM_Ruins_Player_Pedestal_Inner"));
		FindAndSetStaticMesh(Ruins_Player_Pedestal_Inner, Ruins_Player_Pedestal_InnerMeshObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> Ruins_Player_Pedestal_InnerSourceMaterialInterfaceObj(TEXT("/Game/MagicTrigger/Materials/Items/Pedestal/MI_Ruins_Player_Pedestal"));
		FindAndSetMaterial(Ruins_Player_Pedestal_Inner, 0, Ruins_Player_Pedestal_InnerSourceMaterialInterfaceObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> Ruins_Player_Pedestal_InnerSourceMaterialInterfaceObj1(TEXT("/Game/MagicTrigger/Materials/Items/Pedestal/MI_Ruins_Player_Pedestal_Metal"));
		FindAndSetMaterial(Ruins_Player_Pedestal_Inner, 1, Ruins_Player_Pedestal_InnerSourceMaterialInterfaceObj1);
		Ruins_Player_Pedestal_Inner->SetCollisionProfileName(FName(TEXT("BlockAll")), false);

		//Ruins_GreenBuffFloor
		Ruins_GreenBuffFloor->SetupAttachment(Ruins_Player_Pedestal_Inner);
		Ruins_GreenBuffFloor->SetRelativeLocation(FVector(0, 0, -8.5), false, &HitResultTmp, ETeleportType::None);
		Ruins_GreenBuffFloor->SetRelativeScale3D(FVector(0.25, 0.25, 0.3));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Ruins_GreenBuffFloorMeshObj(TEXT("/Game/MagicTrigger/Meshes/Items/Pedestal/SM_Ruins_GreenBuffFloor"));
		FindAndSetStaticMesh(Ruins_GreenBuffFloor, Ruins_GreenBuffFloorMeshObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> Ruins_GreenBuffFloorSourceMaterialInterfaceObj(TEXT("/Game/MagicTrigger/Materials/Items/Pedestal/MI_Ruins_BuffFloorA"));
		FindAndSetMaterial(Ruins_GreenBuffFloor, 0, Ruins_GreenBuffFloorSourceMaterialInterfaceObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> Ruins_GreenBuffFloorSourceMaterialInterfaceObj1(TEXT("/Game/MagicTrigger/Materials/Items/Pedestal/MI_Ruins_BuffFloorB"));
		FindAndSetMaterial(Ruins_GreenBuffFloor, 1, Ruins_GreenBuffFloorSourceMaterialInterfaceObj1);
		Ruins_GreenBuffFloor->SetCollisionProfileName(FName(TEXT("BlockAll")), false);

		//Ruins_Buff_Floor_Lower
		Ruins_Buff_Floor_Lower->SetupAttachment(GetRootComponent());
		Ruins_Buff_Floor_Lower->SetRelativeLocation(FVector(0, 0, -41), false, &HitResultTmp, ETeleportType::None);
		Ruins_Buff_Floor_Lower->SetRelativeScale3D(FVector(0.85, 0.85, 1));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Ruins_Buff_Floor_LowerMeshObj(TEXT("/Game/MagicTrigger/Meshes/Items/Pedestal/SM_Ruins_Buff_Floor_Lower"));
		FindAndSetStaticMesh(Ruins_Buff_Floor_Lower, Ruins_Buff_Floor_LowerMeshObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> Ruins_Buff_Floor_LowerSourceMaterialInterfaceObj(TEXT("/Game/MagicTrigger/Materials/Items/Pedestal/MI_Ruins_BuffFloorA"));
		FindAndSetMaterial(Ruins_Buff_Floor_Lower, 0, Ruins_Buff_Floor_LowerSourceMaterialInterfaceObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> Ruins_Buff_Floor_LowerSourceMaterialInterfaceObj1(TEXT("/Game/MagicTrigger/Materials/Items/Pedestal/MI_Jungle_Metal_Floor"));
		FindAndSetMaterial(Ruins_Buff_Floor_Lower, 1, Ruins_Buff_Floor_LowerSourceMaterialInterfaceObj1);
		Ruins_Buff_Floor_Lower->SetCollisionProfileName(FName(TEXT("BlockAll")), false);

		//JungleTrim_Metal_Whole
		JungleTrim_Metal_Whole->SetupAttachment(Ruins_Buff_Floor_Lower);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> JungleTrim_Metal_WholeMeshObj(TEXT("/Game/MagicTrigger/Meshes/Items/Pedestal/SM_JungleTrim_Metal_Whole"));
		FindAndSetStaticMesh(JungleTrim_Metal_Whole, JungleTrim_Metal_WholeMeshObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> JungleTrim_Metal_WholeSourceMaterialInterfaceObj(TEXT("/Game/MagicTrigger/Materials/Items/Pedestal/MI_Jungle_Metal_Trim"));
		IndicationSourceMaterial = FindAndSetMaterial(JungleTrim_Metal_Whole, 0, JungleTrim_Metal_WholeSourceMaterialInterfaceObj);
		JungleTrim_Metal_Whole->SetCollisionProfileName(FName(TEXT("BlockAll")), false);

		//JungleTrim_Metal_Whole_Little
		JungleTrim_Metal_Whole_Little->SetupAttachment(GetRootComponent());
		JungleTrim_Metal_Whole_Little->SetRelativeLocation(FVector(0, 0, -17), false, &HitResultTmp, ETeleportType::None);
		JungleTrim_Metal_Whole_Little->SetRelativeScale3D(FVector(0.371712, 0.371712, 0.691256));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> JungleTrim_Metal_Whole_LittleMeshObj(TEXT("/Game/MagicTrigger/Meshes/Items/Pedestal/SM_JungleTrim_Metal_Whole"));
		FindAndSetStaticMesh(JungleTrim_Metal_Whole_Little, JungleTrim_Metal_Whole_LittleMeshObj);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> JungleTrim_Metal_Whole_LittleSourceMaterialInterfaceObj(TEXT("/Game/MagicTrigger/Materials/Items/Pedestal/MI_Jungle_Metal_Trim"));
		FindAndSetMaterial(JungleTrim_Metal_Whole_Little, 0, JungleTrim_Metal_Whole_LittleSourceMaterialInterfaceObj);
		Ruins_Buff_Floor_Lower->SetCollisionProfileName(FName(TEXT("BlockAll")), false);

		//Sphere1
		Sphere1->SetupAttachment(SpheresCentralPoint);
		Sphere1->SetRelativeLocation(FVector(0, 509.7, 0), false, &HitResultTmp, ETeleportType::None);
		Sphere1->SetRelativeScale3D(FVector(0.4));
		Sphere1->SetCollisionProfileName(FName(TEXT("NoCollision")), false);
		//Sphere2
		Sphere2->SetupAttachment(SpheresCentralPoint);
		Sphere2->SetRelativeLocation(FVector(448.2, 257.5, 0), false, &HitResultTmp, ETeleportType::None);
		Sphere2->SetRelativeScale3D(FVector(0.4));
		Sphere2->SetCollisionProfileName(FName(TEXT("NoCollision")), false);
		//Sphere3
		Sphere3->SetupAttachment(SpheresCentralPoint);
		Sphere3->SetRelativeLocation(FVector(450, -255.1, 0), false, &HitResultTmp, ETeleportType::None); //(X=449.991486,Y=-255.118729,Z=72.558281)
		Sphere3->SetRelativeScale3D(FVector(0.4));
		Sphere3->SetCollisionProfileName(FName(TEXT("NoCollision")), false);
		//Sphere4
		Sphere4->SetupAttachment(SpheresCentralPoint);
		Sphere4->SetRelativeLocation(FVector(1.4, -513.8, 0), false, &HitResultTmp, ETeleportType::None); //(X=1.363075,Y=-513.788635,Z=72.558281)
		Sphere4->SetRelativeScale3D(FVector(0.4));
		Sphere4->SetCollisionProfileName(FName(TEXT("NoCollision")), false);
		//Sphere5
		Sphere5->SetupAttachment(SpheresCentralPoint);
		Sphere5->SetRelativeLocation(FVector(-444.8, -256.4, 0), false, &HitResultTmp, ETeleportType::None); //(X=-444.788391,Y=-256.352142,Z=72.558281)
		Sphere5->SetRelativeScale3D(FVector(0.4));
		Sphere5->SetCollisionProfileName(FName(TEXT("NoCollision")), false);
		//Sphere6
		Sphere6->SetupAttachment(SpheresCentralPoint);
		Sphere6->SetRelativeLocation(FVector(-447.8, 257.5, 0), false, &HitResultTmp, ETeleportType::None); //(X=-447.796173,Y=257.536499,Z=72.558281)
		Sphere6->SetRelativeScale3D(FVector(0.4));
		Sphere6->SetCollisionProfileName(FName(TEXT("NoCollision")), false);
		//Sphere7
		Sphere7->SetupAttachment(SpheresCentralPoint);
		Sphere7->SetRelativeLocation(FVector(0.2, 0.5, 35.2), false, &HitResultTmp, ETeleportType::None); //(X=0.184109,Y=0.520660,Z=107.810875)
		Sphere7->SetRelativeScale3D(FVector(0.4));
		Sphere7->SetCollisionProfileName(FName(TEXT("NoCollision")), false);

		static ConstructorHelpers::FObjectFinder<UStaticMesh> SpheresMeshObj(TEXT("/Game/MagicTrigger/Meshes/Items/SM_Sphere320"));
		if (SpheresMeshObj.Succeeded())
		{
			Sphere1->SetStaticMesh(SpheresMeshObj.Object);
			Sphere2->SetStaticMesh(SpheresMeshObj.Object);
			Sphere3->SetStaticMesh(SpheresMeshObj.Object);
			Sphere4->SetStaticMesh(SpheresMeshObj.Object);
			Sphere5->SetStaticMesh(SpheresMeshObj.Object);
			Sphere6->SetStaticMesh(SpheresMeshObj.Object);
			Sphere7->SetStaticMesh(SpheresMeshObj.Object);
		}
		else
		{
			DEBUGMESSAGE("!SpheresMeshObj.Succeeded()");
		}

		static ConstructorHelpers::FObjectFinder<UMaterialInterface> SourceMaterialInterfaceObj(TEXT("/Game/MagicTrigger/Materials/Quests/QuestOpenLastDoor/M_SpheresPedestal"));
		if (SourceMaterialInterfaceObj.Succeeded())
		{
			SpheresSourceMaterial = SourceMaterialInterfaceObj.Object;
			Sphere1->SetMaterial(0, SpheresSourceMaterial);
			Sphere2->SetMaterial(0, SpheresSourceMaterial);
			Sphere3->SetMaterial(0, SpheresSourceMaterial);
			Sphere4->SetMaterial(0, SpheresSourceMaterial);
			Sphere5->SetMaterial(0, SpheresSourceMaterial);
			Sphere6->SetMaterial(0, SpheresSourceMaterial);
			Sphere7->SetMaterial(0, SpheresSourceMaterial);

		}
		else
		{
			DEBUGMESSAGE("!SourceMaterialInterfaceObj.Succeeded()");
		}
	}

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AOpenLastDoorPedestalParent::Activate);
}

void AOpenLastDoorPedestalParent::BeginPlay()
{
	Super::BeginPlay();
	SetupMaterials();
	
	CurrentDeltaRotationSpheres = Max1DeltaRotationSpheres;
	GetWorld()->GetTimerManager().SetTimer(RotationComponentsTimer, this, &AOpenLastDoorPedestalParent::RotationComponentsUpdate, TimersDeltaTime, true);
}

void AOpenLastDoorPedestalParent::ReturnToBeginAfterWrongSummaryPlacings()
{
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	float Step = ChangeRotationSpheresTime / TimersDeltaTime;
	RotationSpheresDeltaValue = CurrentDeltaRotationSpheres / Step;
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AOpenLastDoorPedestalParent::DecreaseRotationFromMax2ToZeroUpdate, TimersDeltaTime, true);

	FTimerHandle TmpTimer;
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		bCanWork = true;
		QuestOpenLastDoorManager->bCanWork = true;
	}
	);
	GetWorld()->GetTimerManager().SetTimer(TmpTimer, TmpDelegate, ChangeRotationSpheresTime + RotationAndEmissiveSpheresTime + MoveSpheresTime, false);
}

void AOpenLastDoorPedestalParent::IncreaseRotationSpheresToMax3()
{
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	RotationSpheresDeltaValue = (Max3DeltaRotationSpheres - CurrentDeltaRotationSpheres) / (ChangeRotationSpheresTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AOpenLastDoorPedestalParent::IncreaseRotationSpheresToMax3Update, TimersDeltaTime, true);
}

void AOpenLastDoorPedestalParent::IncreaseRotationSpheresToMax3Update()
{
	CurrentDeltaRotationSpheres += RotationSpheresDeltaValue;
	if (CurrentDeltaRotationSpheres < Max3DeltaRotationSpheres)
	{
		return;
	}
	CurrentDeltaRotationSpheres = Max3DeltaRotationSpheres;
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	SwitchOnPump();
}

void AOpenLastDoorPedestalParent::SwitchOnPump()
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(InflateSphereSpawnPoint->K2_GetComponentLocation());
	SpawnTransform.SetRotation(FQuat(FRotator(0)));
	SpawnTransform.SetScale3D(FVector(0));
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	InflatedSphere = GetWorld()->SpawnActor<AInflatedSphere>(AInflatedSphere::StaticClass(), SpawnTransform, ActorSpawnParameters);

	CountOfUpInflates = 0;
	MovePumpDeltaZ = (HighPoint->GetRelativeLocation().Z - LowerPoint->GetRelativeLocation().Z) / (MoveSpheresHalfTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AOpenLastDoorPedestalParent::MovePumpDownUpdate, TimersDeltaTime, true);
}

void AOpenLastDoorPedestalParent::MovePumpDownUpdate()
{

	if (SpheresCentralPoint->GetRelativeLocation().Z <= LowerPoint->GetRelativeLocation().Z)
	{
		SpheresCentralPoint->SetRelativeLocation(LowerPoint->GetRelativeLocation(), false, &HitResultTmp, ETeleportType::None);
		GetWorld()->GetTimerManager().ClearTimer(MainTimer);
		CountOfDownInflates++;
		if (CountOfUpInflates < MaxCountOfUpInflates)
		{
			InflateSphere();
			GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AOpenLastDoorPedestalParent::MovePumpUpUpdate, TimersDeltaTime, true);
		} 
		else
		{
			MoveIflateSphereToPedestal7();
		}
	} 
	else
	{
		SpheresCentralPoint->AddRelativeLocation(FVector(0, 0, MovePumpDeltaZ * -1), false, &HitResultTmp, ETeleportType::None);
	}
}

void AOpenLastDoorPedestalParent::InflateSphere()
{
	ScaleInflateBigDelta += IncreaseScaleInflateBigDelta;
	ScaleInflateDeltaZ = (ScaleInflateBigDelta.Z - InflatedSphere->GetActorScale3D().Z) / (MoveSpheresHalfTime / TimersDeltaTime);
	ScaleInflateDeltaXY = (ScaleInflateBigDelta.X - InflatedSphere->GetActorScale3D().X) / (MoveSpheresHalfTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(InflateSphereTimer, this, &AOpenLastDoorPedestalParent::InflateSphereUpdate, TimersDeltaTime, true);
}

void AOpenLastDoorPedestalParent::InflateSphereUpdate()
{
	bool ZReached = InflatedSphere->GetActorScale3D().Z >= ScaleInflateBigDelta.Z;
	bool XYReached = InflatedSphere->GetActorScale3D().X >= ScaleInflateBigDelta.X;
	if (ZReached && XYReached)
	{
		InflatedSphere->SetActorScale3D(ScaleInflateBigDelta);
		GetWorld()->GetTimerManager().ClearTimer(InflateSphereTimer);
	} 
	else
	{
		FVector ScaleInflateLittle = FVector
		(
			InflatedSphere->GetActorScale3D().X + ScaleInflateDeltaXY,
			InflatedSphere->GetActorScale3D().Y + ScaleInflateDeltaXY,
			InflatedSphere->GetActorScale3D().Z + ScaleInflateDeltaZ
		);
		InflatedSphere->SetActorScale3D(ScaleInflateLittle);
	}
}

void AOpenLastDoorPedestalParent::MovePumpUpUpdate()
{
	if (SpheresCentralPoint->GetRelativeLocation().Z >= HighPoint->GetRelativeLocation().Z)
	{
		SpheresCentralPoint->SetRelativeLocation(HighPoint->GetRelativeLocation(), false, &HitResultTmp, ETeleportType::None);
		GetWorld()->GetTimerManager().ClearTimer(MainTimer);
		CountOfUpInflates++;
		if (CountOfDownInflates < MaxCountOfDownInflates)
		{
			GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AOpenLastDoorPedestalParent::MovePumpDownUpdate, TimersDeltaTime, true, MoveSpheresTime);
		}
	}
	else
	{
		SpheresCentralPoint->AddRelativeLocation(FVector(0, 0, MovePumpDeltaZ), false, &HitResultTmp, ETeleportType::None);
	}
}

void AOpenLastDoorPedestalParent::MoveIflateSphereToPedestal7()
{
	FVector TargetRelativeLocation = QuestOpenLastDoorManager->PedestalsArray[6]->InflateSphereSpawnPoint->K2_GetComponentLocation();
	FRotator TargetRelativeRotation = InflatedSphere->GetRootComponent()->GetRelativeRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo
	(
		InflatedSphere->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		true,
		true,
		MoveSpheresTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
	FTimerHandle TmpTimer;
	GetWorld()->GetTimerManager().SetTimer(TmpTimer, this, &AOpenLastDoorPedestalParent::DeleteUnusedInflateSpheres, MoveSpheresTime, false);
}

void AOpenLastDoorPedestalParent::DeleteUnusedInflateSpheres()
{
	if (QuestOpenLastDoorManager->PedestalsArray[6] != this)
	{
		InflatedSphere->Destroy();
	} 
	else
	{
		QuestOpenLastDoorManager->IncreaseEmissiveLastInflateSphere();
	}
}

void AOpenLastDoorPedestalParent::FindAndSetStaticMesh(UStaticMeshComponent* InStaticMeshComponent, ConstructorHelpers::FObjectFinder<UStaticMesh>& InMeshObj)
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

UMaterialInterface* AOpenLastDoorPedestalParent::FindAndSetMaterial(UStaticMeshComponent* InStaticMeshComponent, int32 InElementIndex, ConstructorHelpers::FObjectFinder<UMaterialInterface>& InSourceMaterialInterfaceObj)
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

void AOpenLastDoorPedestalParent::SetupMaterials()
{
	SpheresMaterial = Sphere1->CreateAndSetMaterialInstanceDynamicFromMaterial(0, SpheresSourceMaterial);
	SpheresMaterial->SetScalarParameterValue(EmissiveMultiplierName, CurrentEmissive);
	Sphere2->SetMaterial(0, SpheresMaterial);
	Sphere3->SetMaterial(0, SpheresMaterial);
	Sphere4->SetMaterial(0, SpheresMaterial);
	Sphere5->SetMaterial(0, SpheresMaterial);
	Sphere6->SetMaterial(0, SpheresMaterial);
	Sphere7->SetMaterial(0, SpheresMaterial);

	IndicationMaterial = JungleTrim_Metal_Whole->CreateAndSetMaterialInstanceDynamicFromMaterial(0, IndicationSourceMaterial);
	IndicationMaterial->SetScalarParameterValue(EmissivePowerName, IndicationEmissive);

}

void AOpenLastDoorPedestalParent::RotationComponentsUpdate()
{
	SpheresCentralPoint->AddLocalRotation(FRotator(0, CurrentDeltaRotationSpheres, 0), false, &HitResultTmp, ETeleportType::None);
	Ruins_GreenBuffFloor->AddLocalRotation(FRotator(0, DeltaRotationBuffFloor, 0), false, &HitResultTmp, ETeleportType::None);
}

void AOpenLastDoorPedestalParent::Activate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bCanWork)
	{
		return;
	}
	SevenfoldSphere = Cast<ASevenfoldSphere>(OtherActor);
	if (!SevenfoldSphere)
	{
		return;
	}
	bCanWork = false;
	float Step = RotationAndEmissiveSpheresTime / TimersDeltaTime;
	RotationSpheresDeltaValue = Max1DeltaRotationSpheres / Step;
	EmissiveSpheresDeltaValue = MaxEmissive / Step;
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AOpenLastDoorPedestalParent::DecreaseRotationAndEmissiveSpheresUpdate, TimersDeltaTime, true);
}

void AOpenLastDoorPedestalParent::DecreaseRotationAndEmissiveSpheresUpdate()
{
	CurrentDeltaRotationSpheres -= RotationSpheresDeltaValue;
	if (CurrentEmissive > MinEmissive)
	{
		CurrentEmissive -= EmissiveSpheresDeltaValue;
		SpheresMaterial->SetScalarParameterValue(EmissiveMultiplierName, CurrentEmissive);
	}
	if (CurrentDeltaRotationSpheres > 0)
	{
		return;
	}
	CurrentDeltaRotationSpheres = 0;
	CurrentEmissive = MinEmissive;
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	MoveSpheresToHighPoint();

}

void AOpenLastDoorPedestalParent::MoveSpheresToHighPoint()
{
	FVector TargetRelativeLocation = HighPoint->GetRelativeLocation();
	FRotator TargetRelativeRotation = SpheresCentralPoint->GetRelativeRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo
	(
		SpheresCentralPoint,
		TargetRelativeLocation,
		TargetRelativeRotation,
		true,
		true,
		MoveSpheresTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
	FTimerHandle TmpTimer;
	GetWorld()->GetTimerManager().SetTimer(TmpTimer, this, &AOpenLastDoorPedestalParent::CheckOnRightPlacingInThisPedestal, MoveSpheresTime + 1, false);

}

void AOpenLastDoorPedestalParent::CheckOnRightPlacingInThisPedestal()
{
	if (!SevenfoldSphere)
	{
		bRightPlacing = false;
		ReturnToBeginAfterWrongPlacing();
	}
	if (SevenfoldSphere->Number == CountOfSpheres)
	{
		bRightPlacing = true;
		ContinueAfterRightPlacing();
	}
	else
	{
		bRightPlacing = false;
		ReturnToBeginAfterWrongPlacing();
	}
}

void AOpenLastDoorPedestalParent::ContinueAfterRightPlacing()
{
	RotationSpheresDeltaValue = Max2DeltaRotationSpheres / (ChangeRotationSpheresTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AOpenLastDoorPedestalParent::IncreaseRotationSpheresToMax2Update, TimersDeltaTime, true);
}

void AOpenLastDoorPedestalParent::IncreaseRotationSpheresToMax2Update()
{
	CurrentDeltaRotationSpheres += RotationSpheresDeltaValue;
	if (CurrentDeltaRotationSpheres < Max2DeltaRotationSpheres)
	{
		return;
	}
	CurrentDeltaRotationSpheres = Max2DeltaRotationSpheres;
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
}
void AOpenLastDoorPedestalParent::ReturnToBeginAfterWrongPlacing()
{
	FVector TargetRelativeLocation = LowerPoint->GetRelativeLocation();
	FRotator TargetRelativeRotation = SpheresCentralPoint->GetRelativeRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo
	(
		SpheresCentralPoint,
		TargetRelativeLocation,
		TargetRelativeRotation,
		true,
		true,
		MoveSpheresTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
	FTimerHandle TmpTimer;
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AOpenLastDoorPedestalParent::IncreaseRotationAndEmissiveSpheresUpdate, TimersDeltaTime, true);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(TmpTimer, TmpDelegate, MoveSpheresTime, false);
}

void AOpenLastDoorPedestalParent::IncreaseRotationAndEmissiveSpheresUpdate()
{
	CurrentDeltaRotationSpheres += RotationSpheresDeltaValue;
	if (CurrentEmissive < MaxEmissive)
	{
		CurrentEmissive += EmissiveSpheresDeltaValue;
		SpheresMaterial->SetScalarParameterValue(EmissiveMultiplierName, CurrentEmissive);
	}
	if (CurrentDeltaRotationSpheres < Max1DeltaRotationSpheres)
	{
		return;
	}
	CurrentDeltaRotationSpheres = Max1DeltaRotationSpheres;
	CurrentEmissive = MaxEmissive;
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
}

void AOpenLastDoorPedestalParent::DecreaseRotationFromMax2ToZeroUpdate()
{
	CurrentDeltaRotationSpheres -= RotationSpheresDeltaValue;
	if (CurrentDeltaRotationSpheres > 0)
	{
		return;
	}
	CurrentDeltaRotationSpheres = 0;
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	ReturnToBeginAfterWrongPlacing();
}

void AOpenLastDoorPedestalParent::Deactivate()
{
	EmissiveSpheresDeltaValue = CurrentEmissive / (ChangeRotationSpheresTime / TimersDeltaTime);
	RotationSpheresDeltaValue = CurrentDeltaRotationSpheres / (ChangeRotationSpheresTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AOpenLastDoorPedestalParent::DeactivateUpdate, TimersDeltaTime, true);
}

void AOpenLastDoorPedestalParent::DeactivateUpdate()
{
	CurrentDeltaRotationSpheres -= RotationSpheresDeltaValue;
	if (CurrentEmissive > 0)
	{
		CurrentEmissive -= EmissiveSpheresDeltaValue;
		SpheresMaterial->SetScalarParameterValue(EmissiveMultiplierName, CurrentEmissive);
	}
	if (CurrentDeltaRotationSpheres > 0)
	{
		return;
	}
	CurrentDeltaRotationSpheres = 0;
	CurrentEmissive = 0;
	SpheresMaterial->SetScalarParameterValue(EmissiveMultiplierName, CurrentEmissive);
	DeltaRotationBuffFloor = 0;
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
}

