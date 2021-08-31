// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "QuestOpenLastDoorManager.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"
#include "MagicTrigger/AbilitySystem/SevenfoldSphere/SevenfoldSphereComponent.h"
#include "MagicTrigger/Quests/QuestOpenLastDoor/OpenLastDoorPedestal1.h"
#include "MagicTrigger/Quests/QuestOpenLastDoor/OpenLastDoorPedestal2.h"
#include "MagicTrigger/Quests/QuestOpenLastDoor/OpenLastDoorPedestal3.h"
#include "MagicTrigger/Quests/QuestOpenLastDoor/OpenLastDoorPedestal4.h"
#include "MagicTrigger/Quests/QuestOpenLastDoor/OpenLastDoorPedestal5.h"
#include "MagicTrigger/Quests/QuestOpenLastDoor/OpenLastDoorPedestal6.h"
#include "MagicTrigger/Quests/QuestOpenLastDoor/OpenLastDoorPedestal7.h"
#include "MagicTrigger/Quests/QuestOpenLastDoor/LastDoorLevel1.h"
#include "MagicTrigger/Quests/QuestOpenLastDoor/InflatedSphere.h"
#include "Kismet/GameplayStatics.h"
 
// Sets default values
AQuestOpenLastDoorManager::AQuestOpenLastDoorManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PointOfPedestal1 = FVector(-51360, -67763, 125.6); 
	PointOfPedestal2 = FVector(-55315, -67763, 125.6); 
	PointOfPedestal3 = FVector(-51360, -63668, 125.6); 
	PointOfPedestal4 = FVector(-55315, -63668, 125.6); 
	PointOfPedestal5 = FVector(-53318, -67763, 125.6); 
	PointOfPedestal6 = FVector(-53318, -63668, 125.6); 
	PointOfPedestal7 = FVector(-53318, -65767, 125.6); 
	SpawnScalePedestals = FVector(0.5);
	SpawnTransformLastDoor = FTransform(FRotator(0, 90, 0), FVector(-50539, 0, 0), FVector(2)); 
	TimersDeltaTime = 0.017;
	EmissiveSphereTime = 0.2;
	RotationSphereTime = 0.5;
	MaxEmissiveSphere = 250;
	MaxRotationSphere = -83.7;
	MoveSphereTime = 0.8;
	MaxScaleSphere = 8.3;
	ScaleSphereTime = 0.4;
	MaxEmissiveGem = 50;
	EmissiveGemTime = 0.8;
	OpenLastDoorOverTime = 4;
	BeginPlayTimerDeltaTime = 0.2;
	bCanWork = true;
}

// Called when the game starts or when spawned
void AQuestOpenLastDoorManager::BeginPlay()
{
	Super::BeginPlay();
	StartBeginPlayTimer();
	SpawnActors();
}

void AQuestOpenLastDoorManager::StartBeginPlayTimer()
{
	BeginPlayDelegate.BindLambda
	(
		[=]()
	{
		auto PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!PlayerCharacter)
		{
			return;
		}
		auto PlayerCharacterMagicTrigger = Cast<APlayerCharacterMagicTrigger>(PlayerCharacter);
		if (!PlayerCharacterMagicTrigger)
		{
			return;
		}
		auto SevenfoldSphereComponent = PlayerCharacterMagicTrigger->GetSevenfoldSphereComponent();
		if (!SevenfoldSphereComponent)
		{
			return;
		}
		SevenfoldSphereComponent->OnSevenfoldSphereFinish.AddDynamic(this, &AQuestOpenLastDoorManager::SSphereFinish);
		GetWorld()->GetTimerManager().ClearTimer(BeginPlayTimer);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(BeginPlayTimer, BeginPlayDelegate, BeginPlayTimerDeltaTime, true);
}

void AQuestOpenLastDoorManager::SpawnActors()
{
	FTransform SpawnTransform;
	SpawnTransform.SetRotation(FQuat(FRotator(0)));
	SpawnTransform.SetScale3D(SpawnScalePedestals);
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnTransform.SetLocation(PointOfPedestal1);
	PedestalsArray.Add(GetWorld()->SpawnActor<AOpenLastDoorPedestalParent>(AOpenLastDoorPedestal1::StaticClass(), SpawnTransform, ActorSpawnParameters));

	SpawnTransform.SetLocation(PointOfPedestal2);
	PedestalsArray.Add(GetWorld()->SpawnActor<AOpenLastDoorPedestalParent>(AOpenLastDoorPedestal2::StaticClass(), SpawnTransform, ActorSpawnParameters));

	SpawnTransform.SetLocation(PointOfPedestal3);
	PedestalsArray.Add(GetWorld()->SpawnActor<AOpenLastDoorPedestalParent>(AOpenLastDoorPedestal3::StaticClass(), SpawnTransform, ActorSpawnParameters));

	SpawnTransform.SetLocation(PointOfPedestal4);
	PedestalsArray.Add(GetWorld()->SpawnActor<AOpenLastDoorPedestalParent>(AOpenLastDoorPedestal4::StaticClass(), SpawnTransform, ActorSpawnParameters));

	SpawnTransform.SetLocation(PointOfPedestal5);
	PedestalsArray.Add(GetWorld()->SpawnActor<AOpenLastDoorPedestalParent>(AOpenLastDoorPedestal5::StaticClass(), SpawnTransform, ActorSpawnParameters));

	SpawnTransform.SetLocation(PointOfPedestal6);
	PedestalsArray.Add(GetWorld()->SpawnActor<AOpenLastDoorPedestalParent>(AOpenLastDoorPedestal6::StaticClass(), SpawnTransform, ActorSpawnParameters));

	SpawnTransform.SetLocation(PointOfPedestal7);
	PedestalsArray.Add(GetWorld()->SpawnActor<AOpenLastDoorPedestalParent>(AOpenLastDoorPedestal7::StaticClass(), SpawnTransform, ActorSpawnParameters));

	for (const auto Pedestal : PedestalsArray)
	{
		Pedestal->QuestOpenLastDoorManager = this;
	}

	SpawnTransformLastDoor.SetLocation(FVector(SpawnTransformLastDoor.GetLocation().X, PointOfPedestal7.Y, PointOfPedestal7.Z));
	LastDoor = GetWorld()->SpawnActor<ALastDoorLevel1>(ALastDoorLevel1::StaticClass(), SpawnTransformLastDoor, ActorSpawnParameters);
}

void AQuestOpenLastDoorManager::SSphereFinish()
{
	if (!bCanWork)
	{
		return;
	}
	bCanWork = false;

	if (CheckOnRightPlacingsOnEveryPedestal())
	{
		ContinueAfterRightSummaryPlacings();
	} 
	else
	{
		ReturnPedestalsToBeginAfterWrongSummaryPlacings();
	}
}

bool AQuestOpenLastDoorManager::CheckOnRightPlacingsOnEveryPedestal()
{
	for (const auto Pedestal : PedestalsArray)
	{
		if (!Pedestal->bRightPlacing)
		{
			return false;
		}
	}
	return true;
}

void AQuestOpenLastDoorManager::ContinueAfterRightSummaryPlacings()
{
	for (const auto Pedestal : PedestalsArray)
	{
		Pedestal->IncreaseRotationSpheresToMax3();
	}
}

void AQuestOpenLastDoorManager::ReturnPedestalsToBeginAfterWrongSummaryPlacings()
{
	for (const auto Pedestal : PedestalsArray)
	{
		Pedestal->ReturnToBeginAfterWrongSummaryPlacings();
	}
}

void AQuestOpenLastDoorManager::IncreaseEmissiveLastInflateSphere()
{
	InflatedSphere = PedestalsArray[6]->InflatedSphere;
	EmissiveSphereDeltaValue = MaxEmissiveSphere / (EmissiveSphereTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AQuestOpenLastDoorManager::IncreaseEmissiveInflateSphereUpdate, TimersDeltaTime, true);
}

void AQuestOpenLastDoorManager::IncreaseEmissiveInflateSphereUpdate()
{
	CurrentEmissiveSphere += EmissiveSphereDeltaValue;
	InflatedSphere->Material->SetScalarParameterValue(InflatedSphere->EmissiveMultiplierName, CurrentEmissiveSphere);
	if (CurrentEmissiveSphere < MaxEmissiveSphere)
	{
		return;
	}
	CurrentEmissiveSphere = MaxEmissiveSphere;
	InflatedSphere->Material->SetScalarParameterValue(InflatedSphere->EmissiveMultiplierName, CurrentEmissiveSphere);
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	IncreaseRotationInflateSphere();
}

void AQuestOpenLastDoorManager::IncreaseRotationInflateSphere()
{
	CurrentRotationSphere = 0;
	RotationSphereDeltaValue = MaxRotationSphere / (RotationSphereTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AQuestOpenLastDoorManager::IncreaseRotationInflateSphereUpdate, TimersDeltaTime, true);
}

void AQuestOpenLastDoorManager::IncreaseRotationInflateSphereUpdate()
{
	CurrentRotationSphere += RotationSphereDeltaValue;
	InflatedSphere->SetActorRotation(FRotator(CurrentRotationSphere, InflatedSphere->GetActorRotation().Yaw, InflatedSphere->GetActorRotation().Roll));
	if (CurrentRotationSphere < MaxRotationSphere)
	{
		return;
	}
	CurrentRotationSphere = MaxRotationSphere;
	InflatedSphere->SetActorRotation(FRotator(CurrentRotationSphere, InflatedSphere->GetActorRotation().Yaw, InflatedSphere->GetActorRotation().Roll));
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	MoveAndScaleInflateSphere();
}

void AQuestOpenLastDoorManager::MoveAndScaleInflateSphere()
{
	FVector TargetRelativeLocation = LastDoor->Gem->K2_GetComponentLocation();
	FRotator TargetRelativeRotation = InflatedSphere->GetRootComponent()->GetRelativeRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo
	(
		InflatedSphere->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		MoveSphereTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
	IncreaseScaleInflateSphere();

}

void AQuestOpenLastDoorManager::IncreaseScaleInflateSphere()
{
	CurrentScaleSphere = InflatedSphere->GetActorScale3D().Z;
	ScaleSphereDeltaValue = (MaxScaleSphere - CurrentScaleSphere) / (ScaleSphereTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AQuestOpenLastDoorManager::IncreaseScaleInflateSphereUpdate, TimersDeltaTime, true);
}

void AQuestOpenLastDoorManager::IncreaseScaleInflateSphereUpdate()
{
	CurrentScaleSphere += ScaleSphereDeltaValue;
	InflatedSphere->SetActorScale3D(FVector(InflatedSphere->GetActorScale3D().X, InflatedSphere->GetActorScale3D().Y, CurrentScaleSphere));
	if (CurrentScaleSphere < MaxScaleSphere)
	{
		return;
	}
	CurrentScaleSphere = MaxScaleSphere;
	InflatedSphere->SetActorScale3D(FVector(InflatedSphere->GetActorScale3D().X, InflatedSphere->GetActorScale3D().Y, CurrentScaleSphere));
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	DecreaseScaleInflateSphere();
}

void AQuestOpenLastDoorManager::DecreaseScaleInflateSphere()
{
	CurrentScaleSphere = InflatedSphere->GetActorScale3D().Z;
	ScaleSphereDeltaValue = CurrentScaleSphere / (ScaleSphereTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AQuestOpenLastDoorManager::DecreaseScaleInflateSphereUpdate, TimersDeltaTime, true);
}

void AQuestOpenLastDoorManager::DecreaseScaleInflateSphereUpdate()
{
	CurrentScaleSphere -= ScaleSphereDeltaValue;
	InflatedSphere->SetActorScale3D(FVector(InflatedSphere->GetActorScale3D().X, InflatedSphere->GetActorScale3D().Y, CurrentScaleSphere));
	if (CurrentScaleSphere > 0)
	{
		return;
	}
	CurrentScaleSphere = 0;
	InflatedSphere->SetActorScale3D(FVector(CurrentScaleSphere));
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	InflatedSphere->Destroy();
	InflatedSphere = nullptr;
	IncreaseEmissiveGem();
}

void AQuestOpenLastDoorManager::IncreaseEmissiveGem()
{
	CurrentEmissiveGem = 0;
	EmissiveGemDeltaValue = MaxEmissiveGem / (EmissiveGemTime / TimersDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(MainTimer, this, &AQuestOpenLastDoorManager::IncreaseEmissiveGemUpdate, TimersDeltaTime, true);
}

void AQuestOpenLastDoorManager::IncreaseEmissiveGemUpdate()
{
	CurrentEmissiveGem += MaxEmissiveGem;
	LastDoor->GemMaterial->SetVectorParameterValue(LastDoor->EmissiveColorMultiName, FLinearColor(FVector4(0, 0, CurrentEmissiveGem, 1)));
	if (CurrentEmissiveGem < MaxEmissiveGem)
	{
		return;
	}
	CurrentEmissiveGem = MaxEmissiveGem;
	LastDoor->GemMaterial->SetVectorParameterValue(LastDoor->EmissiveColorMultiName, FLinearColor(FVector4(0, 0, CurrentEmissiveGem, 1)));
	GetWorld()->GetTimerManager().ClearTimer(MainTimer);
	DeactivatePedestals();
	OpenLastDoor();
}

void AQuestOpenLastDoorManager::DeactivatePedestals()
{
	bCanWork = false;
	for (const auto Pedestal : PedestalsArray)
	{
		if (Pedestal)
		{
			Pedestal->Deactivate();
		}
	}
}

void AQuestOpenLastDoorManager::OpenLastDoor()
{
	FVector TargetRelativeLocation = LastDoor->DoorOpenPoint->GetRelativeLocation();
	FRotator TargetRelativeRotation = LastDoor->Door->GetRelativeRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo
	(
		LastDoor->Door,
		TargetRelativeLocation,
		TargetRelativeRotation,
		true,
		true,
		OpenLastDoorOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

