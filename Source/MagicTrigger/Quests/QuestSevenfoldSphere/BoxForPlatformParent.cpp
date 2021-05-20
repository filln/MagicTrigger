// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * боксы для расстановки на платформы для квеста.
 */


#include "BoxForPlatformParent.h"
#include "Kismet\KismetSystemLibrary.h"

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
	this->InitialLocation = GetActorLocation();
}

void ABoxForPlatformParent::MoveToInitialLocation()
{
	SetEnableInteraction(false);
	MoveUp();
}

void ABoxForPlatformParent::MoveUp()
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetRelativeLocation = FVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + this->MoveUpHigh);
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
		this->MoveUpOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABoxForPlatformParent::MoveHorizontal, this->MoveUpOverTime);
}

void ABoxForPlatformParent::MoveHorizontal()
{
	FVector TargetRelativeLocation = FVector(this->InitialLocation.X, this->InitialLocation.Y, this->InitialLocation.Z + this->MoveUpHigh);
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
		this->MoveHorizontalOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABoxForPlatformParent::MoveDown, this->MoveHorizontalOverTime);
}

void ABoxForPlatformParent::MoveDown()
{
	FVector TargetRelativeLocation = this->InitialLocation;
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
		this->MoveDownOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ABoxForPlatformParent::SetEnableInteraction, true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, this->MoveDownOverTime, false);
}

void ABoxForPlatformParent::SetEnableInteraction(bool bInEnable)
{
	SetActorEnableCollision(bInEnable);
	this->StaticMesh->SetSimulatePhysics(bInEnable);
}
