// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * боксы для расстановки на платформы для квеста.
 */


#include "BoxForPlatformParent.h"
#include "Kismet/KismetSystemLibrary.h"

ABoxForPlatformParent::ABoxForPlatformParent()
{
	MoveUpOverTime = 2;
	MoveHorizontalOverTime = 3;
	MoveDownOverTime = 2;
	MoveUpHigh = 100;
}

void ABoxForPlatformParent::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
}

void ABoxForPlatformParent::MoveToInitialLocation()
{
	SetEnableInteraction(false);
	MoveUp();
}

void ABoxForPlatformParent::MoveUp()
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetRelativeLocation = FVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + MoveUpHigh);
	FRotator TargetRelativeRotation = GetActorRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		MoveUpOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABoxForPlatformParent::MoveHorizontal, MoveUpOverTime);
}

void ABoxForPlatformParent::MoveHorizontal()
{
	FVector TargetRelativeLocation = FVector(InitialLocation.X, InitialLocation.Y, InitialLocation.Z + MoveUpHigh);
	FRotator TargetRelativeRotation = GetActorRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		MoveHorizontalOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABoxForPlatformParent::MoveDown, MoveHorizontalOverTime);
}

void ABoxForPlatformParent::MoveDown()
{
	FVector TargetRelativeLocation = InitialLocation;
	FRotator TargetRelativeRotation = GetActorRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		MoveDownOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ABoxForPlatformParent::SetEnableInteraction, true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, MoveDownOverTime, false);
}

void ABoxForPlatformParent::SetEnableInteraction(bool bInEnable)
{
	SetActorEnableCollision(bInEnable);
	StaticMesh->SetSimulatePhysics(bInEnable);
}
