// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для поднимания или опускания поднимаемых предметов.
 */


#include "UpDownLiftingItemComponent.h"
#include "MagicTrigger\Interfaces\PlayerCharacterInterface.h"
#include "MagicTrigger\Interfaces\LiftingItemInterface.h"
#include "MagicTrigger\Interfaces\OwnerTargetSelectionInterface.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

class ALiftingItem;

// Sets default values for this component's properties
UUpDownLiftingItemComponent::UUpDownLiftingItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	DistanceOfTraceObstacle = 100;
	DeltaVerticalTraceZ = 20;
	//DrawDebugType = EDrawDebugTrace::None;
	TraceCollisionChannel = ECollisionChannel::ECC_Visibility;
	bDrawDebugTrace = false;
	DetachOverTime = 0.3;
	AttachOverTime = 0.2;
	StartTraceObstacleSocketName = FName(TEXT("Hips"));

}


// Called when the game starts
void UUpDownLiftingItemComponent::BeginPlay()
{
	Super::BeginPlay();

	this->Owner = GetOwner();

	if (this->Owner)
	{
		if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->Owner))
		{
			this->OwnersMesh = IPlayerCharacterInterface::Execute_GetMesh_IF(this->Owner);
		}

		if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->Owner))
		{
			this->InterractCollision = IPlayerCharacterInterface::Execute_GetInteractCollision_IF(this->Owner);
		}

	}
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
		PointPutDownTransform = IPlayerCharacterInterface::Execute_GetPointPutDownTransform_IF(this->Owner);
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
	if (!this->LiftUpObject || !this->OwnersMesh)
	{
		return;
	}


	if (IsInterfaceImplementedBy<ILiftingItemInterface>(this->LiftUpObject))
	{
		this->AttachSocket = ILiftingItemInterface::Execute_GetAttachSocket_IF(this->LiftUpObject);
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
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	this->LiftUpObject->AttachToComponent(this->OwnersMesh, AttachmentTransformRules, this->AttachSocket);
}


void UUpDownLiftingItemComponent::LiftUp()
{
	if (this->LiftUpObject || !this->Owner)
	{
		return;
	}

	this->LiftUpObject = FindLifUpObject();

	if (!this->LiftUpObject)
	{
		return;
	}

	if (IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(this->Owner))
	{
		IOwnerTargetSelectionInterface::Execute_OffWatchingActors_IF(this->Owner);
	}

	if (IsInterfaceImplementedBy<ILiftingItemInterface>(this->LiftUpObject))
	{
		ILiftingItemInterface::Execute_SetPlayingAnimationLiftUp_IF(this->LiftUpObject, true);
	}

}

void UUpDownLiftingItemComponent::PutDown()
{
	if (!this->LiftUpObject)
	{
		return;
	}

	if (TraceObstacle())
	{
		return;
	}

	if (!TracePutDownPoint())
	{
		return;
	}

	if (IsInterfaceImplementedBy<ILiftingItemInterface>(this->LiftUpObject))
	{
		ILiftingItemInterface::Execute_SetPlayingAnimationPutDown_IF(this->LiftUpObject, true);
	}
}

void UUpDownLiftingItemComponent::DestroyLiftingActor()
{
	if (!this->LiftUpObject)
	{
		return;
	}

	bool bDestroyed = this->LiftUpObject->Destroy();
	if (bDestroyed)
	{
		this->LiftUpObject = nullptr;
	}
}

AActor* UUpDownLiftingItemComponent::FindLifUpObject()
{
	AActor* LiftUpObjectTmp = nullptr;


	if (!this->InterractCollision || !this->LiftUpClass)
	{
		return LiftUpObjectTmp;
	}

	TArray<AActor*> OverlappingActorsArr;
	this->InterractCollision->GetOverlappingActors(OverlappingActorsArr, this->LiftUpClass);

	if (!OverlappingActorsArr.Num())
	{
		return LiftUpObjectTmp;
	}

	AActor* ObservedActor = nullptr;
	if (IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(this->Owner))
	{
		ObservedActor = IOwnerTargetSelectionInterface::Execute_GetObservedActor_IF(this->Owner);
	}

	if (ObservedActor)
	{
		for (const auto& CurrentActor : OverlappingActorsArr)
		{
			if (!CurrentActor)
			{
				continue;
			}

			if (CurrentActor == ObservedActor)
			{
				return CurrentActor;
			}
		}
	}
	else
	{
		for (const auto& CurrentActor : OverlappingActorsArr)
		{
			if (CurrentActor)
			{
				return CurrentActor;
			}
		}
	}

	return LiftUpObjectTmp;
}

bool UUpDownLiftingItemComponent::TracePutDownPoint()
{
	if (!this->Owner || !GetWorld())
	{
		return false;
	}

	FTransform StartTraceTransform;
	FTransform EndTraceTransform;
	if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->Owner))
	{
		StartTraceTransform = IPlayerCharacterInterface::Execute_GetPointStartTraceToPutDownPointTransform_IF(this->Owner);
		EndTraceTransform = IPlayerCharacterInterface::Execute_GetPointPutDownTransform_IF(this->Owner);
	}

	FVector StartTrace = StartTraceTransform.GetLocation();
	FVector EndTrace = EndTraceTransform.GetLocation();
	EndTrace.Z = EndTrace.Z - this->DeltaVerticalTraceZ;

	FName TraceTag = FName(TEXT("TracePutDownPoint"));
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(TraceTag, FCollisionQueryParams::GetUnknownStatId());
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this->Owner);
	IgnoredActors.Add(this->LiftUpObject);
	CollisionQueryParams.AddIgnoredActors(IgnoredActors);

	FCollisionResponseParams CollisionResponseParams;


	if (this->bDrawDebugTrace)
	{
		GetWorld()->DebugDrawTraceTag = TraceTag;
	}
	else
	{
		GetWorld()->DebugDrawTraceTag = FName();
	}

	bool bTraceResult = GetWorld()->LineTraceSingleByChannel(this->DetachLiftingActorTraceOut, StartTrace, EndTrace, this->TraceCollisionChannel, CollisionQueryParams, CollisionResponseParams);

	return bTraceResult;
}

bool UUpDownLiftingItemComponent::TraceObstacle()
{
	if (!this->Owner)
	{
		return true;
	}

	FTransform StartTraceObstacleSocketNameTransform;
	FVector UpDownLiftingArrowForwardVector;
	if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->Owner))
	{
		StartTraceObstacleSocketNameTransform = IPlayerCharacterInterface::Execute_GetSocketTransform_IF(this->Owner, this->StartTraceObstacleSocketName);
		UpDownLiftingArrowForwardVector = IPlayerCharacterInterface::Execute_GetUpDownLiftingArrowForwardVector_IF(this->Owner);
	}

	FVector StartTrace = StartTraceObstacleSocketNameTransform.GetLocation();
	FVector EndTrace = StartTrace + UpDownLiftingArrowForwardVector * this->DistanceOfTraceObstacle;

	FName TraceTag = FName(TEXT("TraceObstacle"));
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(TraceTag, FCollisionQueryParams::GetUnknownStatId());
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this->Owner);
	IgnoredActors.Add(this->LiftUpObject);
	CollisionQueryParams.AddIgnoredActors(IgnoredActors);

	FCollisionResponseParams CollisionResponseParams;


	if (this->bDrawDebugTrace)
	{
		GetWorld()->DebugDrawTraceTag = TraceTag;
	}
	else
	{
		GetWorld()->DebugDrawTraceTag = FName();
	}

	FHitResult HitResultTmp;
	bool bTraceResult = GetWorld()->LineTraceSingleByChannel(HitResultTmp, StartTrace, EndTrace, this->TraceCollisionChannel, CollisionQueryParams, CollisionResponseParams);

	return bTraceResult;

}

