// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 


#include "SevenfoldSphereComponent.h"
#include "MagicTrigger/AbilitySystem/AbilitySystemManager.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/AbilitySystem/SevenfoldSphere/FirstCopiesOfSSphere.h"
#include "MagicTrigger/AbilitySystem/SevenfoldSphere/LastCopyOfSSphere.h"
#include "MagicTrigger/Enemy/EnemyCharacterMagicTrigger.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USevenfoldSphereComponent::USevenfoldSphereComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CountOfSpheres = 0;
	bUsePossible = true;
	SpawnScale = FVector(1.5);
	AttachSocket = FName(TEXT("PickUpRightHand"));
	MoveFirstSpheresToLastOverTime = 3;
	DeltaYawDegree = 3;
	MaxEmissiveFirstSpheres = 5;
	CurrentEmissiveFirstSpheres = 0;
	CurrentEmissiveLastSphere = 0;
	CurrentScaleLastSphereMultiplier = 1;
	IncreaseMiddleScaleLastSphereTime = 0.5;
	IncreaseScaleAndEmissiveLastSphereTime = 0.5;
	MaxEmissiveLastSphere = 400;
	MaxMiddleScaleLastSphereMultiplier = 5;
	MaxScaleLastSphereMultiplier = 3;
	CurrentOpacityLastSphere = 1;
	TimersDeltaTime = 0.017;
	Damage = 100;
}


// Called when the game starts
void USevenfoldSphereComponent::BeginPlay()
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
	DeltaEmissiveFirstSpheres = MaxEmissiveFirstSpheres / (MoveFirstSpheresToLastOverTime / TimersDeltaTime);
	DeltaEmissiveLastSphere = MaxEmissiveLastSphere / (IncreaseScaleAndEmissiveLastSphereTime / TimersDeltaTime);
	DeltaMiddleScaleLastSphereMultiplier = MaxMiddleScaleLastSphereMultiplier / (IncreaseMiddleScaleLastSphereTime / TimersDeltaTime);
	DeltaScaleLastSphereMultiplier = MaxScaleLastSphereMultiplier / (IncreaseScaleAndEmissiveLastSphereTime / TimersDeltaTime);
	DeltaOpacityLastSphere = CurrentOpacityLastSphere / (IncreaseScaleAndEmissiveLastSphereTime / TimersDeltaTime);
	CountTimerStep = int(MoveFirstSpheresToLastOverTime / TimersDeltaTime);
}


void USevenfoldSphereComponent::Use()
{
	if (!bUsePossible)
	{
		return;
	}
	if (CountOfSpheres < 7)
	{
		AbilitySystemManager->UseSSphereAttack();
	}
	if (CountOfSpheres == 7)
	{
		bUsePossible = false;
		ActivateAbility();
	}
}

void USevenfoldSphereComponent::SpawnSSphere()
{
	FTransform SocketTransform = AbilitySystemManager->GetSocketTransform(AttachSocket);
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketTransform.GetLocation());
	SpawnTransform.SetRotation(FQuat(FRotator(0)));
	SpawnTransform.SetScale3D(SpawnScale);
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (CountOfSpheres == 6)
	{
		LastSSphere = GetWorld()->SpawnActor<ALastCopyOfSSphere>(ALastCopyOfSSphere::StaticClass(), SpawnTransform, ActorSpawnParameters);
		if (LastSSphere)
		{
			IncreaseCountOfSpheres();
		}
	}
	else
	{
		AFirstCopiesOfSSphere* FirstCopyOfSphere = GetWorld()->SpawnActor<AFirstCopiesOfSSphere>(AFirstCopiesOfSSphere::StaticClass(), SpawnTransform, ActorSpawnParameters);
		if (FirstCopyOfSphere)
		{
			SpheresArray.Add(FirstCopyOfSphere);
			IncreaseCountOfSpheres();
			FirstCopyOfSphere->Number = GetCountOfSpheres();
		}
	}

}

int USevenfoldSphereComponent::GetCountOfSpheres() const
{
	return CountOfSpheres;
}

void USevenfoldSphereComponent::IncreaseCountOfSpheres()
{
	CountOfSpheres++;
	AbilitySystemManager->SetCountOfSpheresText();
}

void USevenfoldSphereComponent::ResetCountOfSpheres()
{
	CountOfSpheres = 0;
	AbilitySystemManager->SetCountOfSpheresText();
}

void USevenfoldSphereComponent::ActivateAbility()
{
	if (!LastSSphere)
	{
		DEBUGMESSAGE("!LastSSphere");
		return;
	}
	if (SpheresArray.Num() < 6)
	{
		DEBUGMESSAGE("SpheresArray.Num() < 6");
		return;
	}
	RotateAndOffsetFirstSpheresAroundLast();
	IncreaseEmissiveFirstSpheres();
	IncreaseToMiddleScaleLastSphere();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USevenfoldSphereComponent::ActivateLastSphere, MoveFirstSpheresToLastOverTime, false);
}

void USevenfoldSphereComponent::RotateAndOffsetFirstSpheresAroundLast()
{
	if (CountTimerStep == 0)
	{
		DEBUGMESSAGE("CountTimerStep == 0");
		return;
	}
	CurrentStep = CountTimerStep;
	FVector LastSSphereLocation = LastSSphere->GetActorLocation();
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		if (CurrentStep == 0)
		{
			return;
		}
		for (const auto Sphere : SpheresArray)
		{
			FVector CurrentLocation = Sphere->GetActorLocation();
			FVector BeforeRotate = CurrentLocation - LastSSphereLocation;
			FVector AfterRotate = BeforeRotate.RotateAngleAxis(DeltaYawDegree, FVector(0, 0, 1));
			FVector BasicOffset = AfterRotate / CurrentStep;
			FVector AfterRotateAndOffset = BasicOffset * (CurrentStep - 1);
			FVector LocationAfterRotateAndOffset = LastSSphereLocation + AfterRotateAndOffset;
			Sphere->SetActorLocation(LocationAfterRotateAndOffset);
		}
		CurrentStep--;
	}
	);
	GetWorld()->GetTimerManager().SetTimer(RotateAndOffsetFirstSpheresTimer, TmpDelegate, TimersDeltaTime, true);
}

void USevenfoldSphereComponent::IncreaseEmissiveFirstSpheres()
{
	CurrentEmissiveFirstSpheres = 0;
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		for (const auto Sphere : SpheresArray)
		{
			CurrentEmissiveFirstSpheres += DeltaEmissiveFirstSpheres;
			Sphere->Material->SetScalarParameterValue(Sphere->EmissiveMultiplierName, CurrentEmissiveFirstSpheres);
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(IncreaseEmissiveFirstSpheresTimer, TmpDelegate, TimersDeltaTime, true);
}

void USevenfoldSphereComponent::IncreaseToMiddleScaleLastSphere()
{
	LastSSphere->InitialScale = LastSSphere->GetActorScale3D();
	CurrentScaleLastSphereMultiplier = 1;
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{

		if (CurrentScaleLastSphereMultiplier >= MaxMiddleScaleLastSphereMultiplier)
		{
			GetWorld()->GetTimerManager().ClearTimer(LastSphereTimer);
			return;
		}
		CurrentScaleLastSphereMultiplier += DeltaMiddleScaleLastSphereMultiplier;
		LastSSphere->SetActorScale3D(CurrentScaleLastSphereMultiplier * LastSSphere->InitialScale);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(LastSphereTimer, TmpDelegate, TimersDeltaTime, true);
}

void USevenfoldSphereComponent::ActivateLastSphere()
{
	DestroyFirstSpheres();
	IncreaseScaleAndEmissiveLastSphere();
}

void USevenfoldSphereComponent::DestroyFirstSpheres()
{
	GetWorld()->GetTimerManager().ClearTimer(RotateAndOffsetFirstSpheresTimer);
	GetWorld()->GetTimerManager().ClearTimer(IncreaseEmissiveFirstSpheresTimer);
	for (const auto Sphere : SpheresArray)
	{
		Sphere->Destroy();
	}
	SpheresArray.Empty();
}

void USevenfoldSphereComponent::IncreaseScaleAndEmissiveLastSphere()
{
	LastSSphere->InitialScale = LastSSphere->GetActorScale3D();
	CurrentScaleLastSphereMultiplier = 1;
	CurrentEmissiveLastSphere = 0;
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{

		if (CurrentEmissiveLastSphere >= MaxEmissiveLastSphere || CurrentScaleLastSphereMultiplier >= MaxScaleLastSphereMultiplier)
		{
			GetWorld()->GetTimerManager().ClearTimer(LastSphereTimer);
			DoDamage();
			DecreaseEmissiveLastSphere();
			return;
		}

		CurrentEmissiveLastSphere += DeltaEmissiveLastSphere;
		LastSSphere->Material->SetScalarParameterValue(LastSSphere->EmissiveMultiplierName, CurrentEmissiveLastSphere);

		CurrentScaleLastSphereMultiplier += DeltaScaleLastSphereMultiplier;
		LastSSphere->SetActorScale3D(CurrentScaleLastSphereMultiplier * LastSSphere->InitialScale);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(LastSphereTimer, TmpDelegate, TimersDeltaTime, true);
}

void USevenfoldSphereComponent::DoDamage()
{
	TArray<AActor*> DamagedActors;
	LastSSphere->Box->GetOverlappingActors(DamagedActors, AEnemyCharacterMagicTrigger::StaticClass());
	if (DamagedActors.Num() == 0)
	{
		return;
	}
	for (const auto DamagedActor : DamagedActors)
	{
		UGameplayStatics::ApplyDamage(DamagedActor, Damage, AbilitySystemManager->GetPlayerController(), AbilitySystemManager->GetPlayerCharacter(), nullptr);
	}
}

void USevenfoldSphereComponent::DecreaseEmissiveLastSphere()
{
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{

		if (CurrentEmissiveLastSphere <= 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(LastSphereTimer);
			DecreaseOpacityLastSphere();
			return;
		}
		CurrentEmissiveLastSphere -= DeltaEmissiveLastSphere;
		LastSSphere->Material->SetScalarParameterValue(LastSSphere->EmissiveMultiplierName, CurrentEmissiveLastSphere);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(LastSphereTimer, TmpDelegate, TimersDeltaTime, true);
}

void USevenfoldSphereComponent::DecreaseOpacityLastSphere()
{
	CurrentOpacityLastSphere = 1;
	LastSSphere->Material = LastSSphere->Mesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, LastSSphere->SourceMaterialTranslucent);
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{

		if (CurrentOpacityLastSphere <= 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(LastSphereTimer);
			Finish();
			return;
		}
		CurrentOpacityLastSphere -= DeltaOpacityLastSphere;
		LastSSphere->Material->SetScalarParameterValue(LastSSphere->OpacityName, CurrentOpacityLastSphere);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(LastSphereTimer, TmpDelegate, TimersDeltaTime, true);
}

void USevenfoldSphereComponent::Finish()
{
	OnSevenfoldSphereFinish.Broadcast();
	ResetCountOfSpheres();
	bUsePossible = true;
	LastSSphere->Destroy();
}

