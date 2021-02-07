// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для поднимания или опускания поднимаемых предметов.
 */


#include "UpDownLiftingItemComponent.h"
#include "MagicTrigger\Interfaces\PlayerCharacterInterface.h"
#include "MagicTrigger\Interfaces\LiftingItemInterface.h"

class ALiftingItem;

// Sets default values for this component's properties
UUpDownLiftingItemComponent::UUpDownLiftingItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	DistanceOfHorizontalTrace = 100;
	DeltaVerticalTraceZ = 20;
	DrawDebugType = EDrawDebugTrace::None;
	TraceChannel = ETraceTypeQuery::TraceTypeQuery1;
	DetachOverTime = 0.3;
	AttachOverTime = 0.2;

}


// Called when the game starts
void UUpDownLiftingItemComponent::BeginPlay()
{
	Super::BeginPlay();

	this->Owner = GetOwner();

}

void UUpDownLiftingItemComponent::DetachLiftingActor()
{
	if (!this->LiftUpObject || !this->Owner)
	{
		return;
	}

	this->LiftUpObject->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false));

	FTransform PointPutDownTransform;
	if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->Owner))
	{
		PointPutDownTransform = IPlayerCharacterInterface::Execute_GetPointPutDownTransform_IF(Owner);
	}

	FVector TargetRelativeLocation = this->DetachLiftingActorTraceOut.Location;
	FRotator TargetRelativeRotation = PointPutDownTransform.Rotator();
	FLatentActionInfo LatentInfo;
	//LatentInfo.CallbackTarget = this;
	//LatentInfo.ExecutionFunction = FName("DoAfterMoveComponentInDetachLiftingActor");
	//LatentInfo.Linkage = 0;
	//LatentInfo.UUID = 0;

	UKismetSystemLibrary::MoveComponentTo
	(
		this->LiftUpObject->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		this->DetachOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUpDownLiftingItemComponent::DoAfterMoveComponentInDetachLiftingActor, this->DetachOverTime);
}
void UUpDownLiftingItemComponent::DoAfterMoveComponentInDetachLiftingActor()
{
	if (IsInterfaceImplementedBy<ILiftingItemInterface>(this->LiftUpObject))
	{
		ILiftingItemInterface::Execute_SetSimulatePhysics_IF(this->LiftUpObject, true);
	}

	this->LiftUpObject->SetActorEnableCollision(true);
	this->LiftUpObject = nullptr;
}

void UUpDownLiftingItemComponent::AttachLiftingActor()
{
	if (!this->LiftUpObject || !this->Owner)
	{
		return;
	}


	if (IsInterfaceImplementedBy<ILiftingItemInterface>(this->LiftUpObject))
	{
		this->AttachSocket = ILiftingItemInterface::Execute_GetAttachSocket_IF(this->LiftUpObject);
	}

	if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->Owner))
	{
		this->OwnersMesh = IPlayerCharacterInterface::Execute_GetMesh_IF(Owner);
	}

	if (IsInterfaceImplementedBy<ILiftingItemInterface>(this->LiftUpObject))
	{
		ILiftingItemInterface::Execute_SetSimulatePhysics_IF(this->LiftUpObject, false);
	}

	this->LiftUpObject->SetActorEnableCollision(false);

	FVector TargetRelativeLocation = this->OwnersMesh->GetSocketLocation(this->AttachSocket);
	FRotator TargetRelativeRotation = this->LiftUpObject->GetRootComponent()->GetSocketRotation(this->AttachSocket);
	FLatentActionInfo LatentInfo;

	UKismetSystemLibrary::MoveComponentTo
	(
		this->LiftUpObject->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		this->AttachOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUpDownLiftingItemComponent::DoAfterMoveComponentInAttachLiftingActor, this->AttachOverTime);

}

void UUpDownLiftingItemComponent::DoAfterMoveComponentInAttachLiftingActor()
{
	FAttachmentTransformRules AttachmentTransformRules;
	AttachmentTransformRules.LocationRule = EAttachmentRule::SnapToTarget;
	AttachmentTransformRules.RotationRule = EAttachmentRule::KeepWorld;
	AttachmentTransformRules.ScaleRule = EAttachmentRule::KeepWorld;
	this->LiftUpObject->AttachToComponent(this->OwnersMesh, AttachmentTransformRules, this->AttachSocket);
}


void UUpDownLiftingItemComponent::LiftUp()
{
	if (this->LiftUpObject || this->Owner)
	{
		return;
	}


}

void UUpDownLiftingItemComponent::PutDown()
{

}

void UUpDownLiftingItemComponent::DestroyLiftingActor()
{

}

AActor* UUpDownLiftingItemComponent::FindLifUpObject()
{
	return this->LiftUpObject;
}

bool UUpDownLiftingItemComponent::TracePutDownPoint()
{
	return true;
}

bool UUpDownLiftingItemComponent::TraceObstacle()
{
	return true;
}

