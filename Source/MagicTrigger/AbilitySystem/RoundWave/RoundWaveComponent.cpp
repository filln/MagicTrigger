// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#include "RoundWaveComponent.h"
#include "MagicTrigger/AbilitySystem/AbilitySystemManager.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/AbilitySystem/RoundWave/RoundWave.h"


// Sets default values for this component's properties
URoundWaveComponent::URoundWaveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	SpawnScale = FVector(0.1);
	ScaleTimerDeltaTime = 0.017;
	MaxScaleMultiplier = 10;
	IncreaseScaleTime = 1.32;
	DecreaseScaleTime = 0.2;
	RoundWaveClass = ARoundWave::StaticClass();
	// ...
}


// Called when the game starts
void URoundWaveComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		DEBUGMESSAGE("!Owner");
		return;
	}
	AbilitySystemManager = Cast<AAbilitySystemManager>(Owner);
	if (!AbilitySystemManager)
	{
		DEBUGMESSAGE("!AbilitySystemManager");
		return;
	}
	
}


void URoundWaveComponent::Use()
{
	AbilitySystemManager->UseRoundWave();
}

void URoundWaveComponent::CastRoundWave()
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(AbilitySystemManager->GetPlayerLocation());
	SpawnTransform.SetRotation(FQuat(FRotator(0)));
	SpawnTransform.SetScale3D(SpawnScale);
	FActorSpawnParameters ActorSpawnParameters;
	RoundWave = GetWorld()->SpawnActor<ARoundWave>(RoundWaveClass, SpawnTransform, ActorSpawnParameters);
	UMaterialInstanceDynamic* Material = RoundWave->Mesh->CreateDynamicMaterialInstance(0, RoundWave->SourceMaterial, FName());
	IncreaseScale();

}

void URoundWaveComponent::EndRoundWave()
{
	DecreaseScale();	
}

void URoundWaveComponent::IncreaseScale()
{
	RoundWave->InitialScale = RoundWave->GetActorScale3D();
	CurrentScaleMultiplier = 1;
	DeltaScaleMultiplier = MaxScaleMultiplier / (IncreaseScaleTime / ScaleTimerDeltaTime);
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
		{

			if (CurrentScaleMultiplier >= MaxScaleMultiplier)
			{
				GetWorld()->GetTimerManager().ClearTimer(ScaleTimer);
				EndRoundWave();
				return;
			}
			CurrentScaleMultiplier += DeltaScaleMultiplier;
			RoundWave->SetActorScale3D(CurrentScaleMultiplier * RoundWave->InitialScale);
		}
	);
	GetWorld()->GetTimerManager().SetTimer(ScaleTimer, TmpDelegate, ScaleTimerDeltaTime, true);
}

void URoundWaveComponent::DecreaseScale()
{
	RoundWave->InitialScale = RoundWave->GetActorScale3D();
	CurrentScaleMultiplier = 1;
	DeltaScaleMultiplier = 1 / (DecreaseScaleTime / ScaleTimerDeltaTime);
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
		{

			if (CurrentScaleMultiplier <= 0)
			{
				GetWorld()->GetTimerManager().ClearTimer(ScaleTimer);
				RoundWave->Destroy();
				RoundWave = nullptr;
				return;
			}
			CurrentScaleMultiplier -= DeltaScaleMultiplier;
			RoundWave->SetActorScale3D(CurrentScaleMultiplier * RoundWave->InitialScale);
		}
	);
	GetWorld()->GetTimerManager().SetTimer(ScaleTimer, TmpDelegate, ScaleTimerDeltaTime, true);
}

